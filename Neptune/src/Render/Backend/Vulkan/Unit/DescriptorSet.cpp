/**
* @file DescriptorPool.cpp.
* @brief The DescriptorPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DescriptorSet.h"

namespace Neptune::Vulkan::Unit {

	DescriptorSet::~DescriptorSet()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkFreeDescriptorSets(m_Device, m_DescriptorPool, 1, &m_Handle);
	}

	void DescriptorSet::AllocateDescriptorSet(VkDevice device, const VkDescriptorSetAllocateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device && info.descriptorPool);

		m_Device = device;
		m_DescriptorPool = info.descriptorPool;

		VK_CHECK(vkAllocateDescriptorSets(device, &info, &m_Handle))
	}

	void DescriptorSet::UpdateDescriptorSet(const VkWriteDescriptorSet& write) const
	{
		NEPTUNE_PROFILE_ZONE

		vkUpdateDescriptorSets(m_Device, 1, &write, 0, nullptr);
	}
}

#endif