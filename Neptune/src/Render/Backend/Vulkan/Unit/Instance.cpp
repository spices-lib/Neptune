#include "Pchheader.h"
#include "Instance.h"

namespace Neptune::Vulkan::Unit {

	Instance::~Instance()
	{
		if (!m_Handle) return;

		vkDestroyInstance(m_Handle, nullptr);
	}

	void Instance::CreateInstance(const VkInstanceCreateInfo& createInfo)
	{
		assert(!m_Handle);

		VK_CHECK(vkCreateInstance(&createInfo, nullptr, &m_Handle))
	}
}