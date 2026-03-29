/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "CommandBuffer.h"
#include "CommandPool.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    CommandBuffer::CommandBuffer(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void CommandBuffer::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        VkCommandBufferAllocateInfo             allocInfo{};
		allocInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool                 = GetCommandPool();
		allocInfo.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount          = 1;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto commandBuffer = CreateSP<Unit::CommandBuffer>();

            commandBuffer->CreateCommandBuffer(GetContext().Get<IDevice>()->Handle(), allocInfo);

            m_CommandBuffers.emplace_back(commandBuffer);

            DEBUGUTILS_SETOBJECTNAME(*commandBuffer, ToString())
        }
    }

    const VkCommandPool& CommandBuffer::GetCommandPool() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (GetEInfrastructure())
		{
			case EInfrastructure::GraphicCommandBuffer:		return GetContext().Get<IGraphicCommandPool>()->Handle();
			case EInfrastructure::ComputeCommandBuffer:     return GetContext().Get<IComputeCommandPool>()->Handle();
			default: return VK_NULL_HANDLE;
		}
    }

    void CommandBuffer::Begin(const VkCommandBufferBeginInfo& info, uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandBuffers[index]->Begin(info);
    }

    void CommandBuffer::End(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandBuffers[index]->End();
    }
}
