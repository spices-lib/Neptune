/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Instance.h"

namespace Neptune::Vulkan::Unit {

	Instance::~Instance()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyInstance(m_Handle, nullptr);
	}

	void Instance::CreateInstance(const VkInstanceCreateInfo& createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		assert(!m_Handle);

		VK_CHECK(vkCreateInstance(&createInfo, nullptr, &m_Handle))
	}
}