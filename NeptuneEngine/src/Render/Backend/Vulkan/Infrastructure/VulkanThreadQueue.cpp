/**
* @file VulkanThreadQueue.cpp.
* @brief The VulkanThreadQueue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanThreadQueue.h"

namespace Neptune {

    VulkanThreadQueue::VulkanThreadQueue(VulkanContext& context)
        : VulkanInfrastructure(context)
    {
        Create();
    }

    void VulkanThreadQueue::Submit(VkCommandBuffer commandBuffer) const
    {
        VkSubmitInfo                     submitInfo{};
		submitInfo.sType               = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount  = 1;
		submitInfo.pCommandBuffers     = &commandBuffer;

		VK_CHECK(vkQueueSubmit(m_Queue, 1, &submitInfo, VK_NULL_HANDLE))
    }

    void VulkanThreadQueue::Wait() const
    {
        VK_CHECK(vkQueueWaitIdle(m_Queue))
    }

    void VulkanThreadQueue::Create()
    {

    }

}

#endif