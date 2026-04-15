/**
* @file Sampler.cpp.
* @brief The Sampler Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Sampler.h"

namespace Neptune::Vulkan::Unit {

	Sampler::~Sampler()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySampler(m_Device, m_Handle, nullptr);
	}

	void Sampler::CreateSampler(VkDevice device, const VkSamplerCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateSampler(device, &info, nullptr, &m_Handle))
	}
}

#endif