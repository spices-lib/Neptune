/**
* @file Semaphore.cpp.
* @brief The Semaphore Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Semaphore.h"

namespace Neptune::Vulkan::Unit {

	Semaphore::~Semaphore()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySemaphore(m_Device, m_Handle, nullptr);
	}

	void Semaphore::CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateSemaphore(device, &info, nullptr, &m_Handle))
	}
}

#endif