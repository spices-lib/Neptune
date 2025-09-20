/**
* @file ThreadQueue.cpp.
* @brief The ThreadQueue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "ThreadQueue.h"

namespace Neptune::Vulkan {

    ThreadQueue::ThreadQueue(Context& context)
        : Infrastructure(context)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void ThreadQueue::Submit(VkCommandBuffer commandBuffer) const
    {
        NEPTUNE_PROFILE_ZONE

        VkSubmitInfo                     submitInfo{};
		submitInfo.sType               = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount  = 1;
		submitInfo.pCommandBuffers     = &commandBuffer;

		VK_CHECK(vkQueueSubmit(m_Handle, 1, &submitInfo, VK_NULL_HANDLE))
    }

    void ThreadQueue::Wait() const
    {
        NEPTUNE_PROFILE_ZONE

        VK_CHECK(vkQueueWaitIdle(m_Handle))
    }

    void ThreadQueue::Create()
    {

    }

}

#endif