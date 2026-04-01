/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Queue.h"
#include "CommandBuffer.h"

namespace Neptune::Vulkan::Unit {

	void Queue::Submit(const VkSubmitInfo& info, VkFence fence) const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkQueueSubmit(m_Handle, 1, &info, fence))
	}

	void Queue::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkQueueWaitIdle(m_Handle))
	}
}