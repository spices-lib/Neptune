/**
* @file Fence.cpp.
* @brief The Fence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Fence.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    Fence::Fence(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Fence::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        VkFenceCreateInfo             fenceInfo{};
		fenceInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto fence = CreateSP<Unit::Fence>();

            fence->CreateFence(GetContext().Get<IDevice>()->Handle(), fenceInfo);
 
            m_Fences.emplace_back(fence);

            DEBUGUTILS_SETOBJECTNAME(*fence, ToString())
        }
    }

    void Fence::Wait(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        auto& fence = m_Fences[index];

        fence->Wait();

        fence->ResetFence();
    }

    void Fence::WaitAll() const
    {
        NEPTUNE_PROFILE_ZONE

        std::ranges::for_each(m_Fences, [](const auto& fence) {
            
            fence->Wait();

            fence->ResetFence();
        });
    }

}