/**
* @file CommandPool.cpp.
* @brief The CommandPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "CommandPool.h"

namespace Neptune::Vulkan::Unit {

	CommandPool::~CommandPool()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyCommandPool(m_Device, m_Handle, nullptr);
	}

	void CommandPool::CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateCommandPool(device, &info, nullptr, &m_Handle))
	}
}

#endif