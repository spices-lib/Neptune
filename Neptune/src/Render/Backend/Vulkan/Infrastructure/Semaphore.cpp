/**
* @file Semaphore.cpp.
* @brief The Semaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Semaphore.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    Semaphore::Semaphore(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Semaphore::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        VkSemaphoreCreateInfo              semaphoreInfo {};
		semaphoreInfo.sType              = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto semaphore = CreateSP<Unit::Semaphore>();

            semaphore->CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

            m_Semaphores.emplace_back(semaphore);

            DEBUGUTILS_SETOBJECTNAME(*semaphore, ToString())
        }
    }

}