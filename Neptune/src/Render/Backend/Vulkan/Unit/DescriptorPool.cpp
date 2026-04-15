/**
* @file DescriptorPool.cpp.
* @brief The DescriptorPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DescriptorPool.h"

namespace Neptune::Vulkan::Unit {

	DescriptorPool::~DescriptorPool()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyDescriptorPool(m_Device, m_Handle, nullptr);
	}

	void DescriptorPool::CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateDescriptorPool(device, &info, nullptr, &m_Handle))
	}
}

#endif