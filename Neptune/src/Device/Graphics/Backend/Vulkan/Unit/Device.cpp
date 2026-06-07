/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Device.h"

namespace Neptune::Vulkan::Unit {

	Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyDevice(m_Handle, nullptr);
	}

	void Device::CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		assert(physicalDevice && createInfo && !m_Handle);

		VK_CHECK(vkCreateDevice(physicalDevice, createInfo, nullptr, &m_Handle))
	}

	VkQueue Device::GetDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		VkQueue queue{};

		vkGetDeviceQueue(m_Handle, queueFamilyIndex, queueIndex, &queue);

		assert(queue);

		return queue;
	}

	void Device::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkDeviceWaitIdle(m_Handle))
	}
}

#endif