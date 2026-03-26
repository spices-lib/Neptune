#include "Pchheader.h"
#include "SamplerYcbcrConversion.h"

namespace Neptune::Vulkan::Unit {

	SamplerYcbcrConversion::~SamplerYcbcrConversion()
	{
		if (!m_Handle) return;

		vkDestroySamplerYcbcrConversion(m_Device, m_Handle, nullptr);
	}

	void SamplerYcbcrConversion::CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		vkCreateSamplerYcbcrConversion(device, &info, nullptr, &m_Handle);
	}

}