/**
* @file SamplerYcbcrConversion.cpp.
* @brief The SamplerYcbcrConversion Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SamplerYcbcrConversion.h"

namespace Neptune::Vulkan::Unit {

	SamplerYcbcrConversion::~SamplerYcbcrConversion()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroySamplerYcbcrConversion(m_Device, m_Handle, nullptr);
	}

	void SamplerYcbcrConversion::CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateSamplerYcbcrConversion(device, &info, nullptr, &m_Handle))
	}

}