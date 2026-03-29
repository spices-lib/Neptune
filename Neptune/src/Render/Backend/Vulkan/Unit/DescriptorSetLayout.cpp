/**
* @file DescriptorSetLayout.cpp.
* @brief The DescriptorSetLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "DescriptorSetLayout.h"

namespace Neptune::Vulkan::Unit {

	DescriptorSetLayout::~DescriptorSetLayout()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyDescriptorSetLayout(m_Device, m_Handle, nullptr);
	}

	void DescriptorSetLayout::CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateDescriptorSetLayout(m_Device, &info, nullptr, &m_Handle))
	}
}