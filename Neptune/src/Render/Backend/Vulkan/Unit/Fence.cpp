/**
* @file Fence.cpp.
* @brief The Fence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Fence.h"

namespace Neptune::Vulkan::Unit {

	Fence::~Fence()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyFence(m_Device, m_Handle, nullptr);
	}

	void Fence::CreateFence(VkDevice device, const VkFenceCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateFence(device, &info, nullptr, &m_Handle))
	}

	void Fence::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkWaitForFences(m_Device, 1, &m_Handle, VK_TRUE, UINT64_MAX))
	}

	void Fence::ResetFence() const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkResetFences(m_Device, 1, &m_Handle))
	}
}