#include "Pchheader.h"
#include "CommandPool.h"

namespace Neptune::Vulkan::Unit {

	CommandPool::~CommandPool()
	{
		if (!m_Handle) return;

		vkDestroyCommandPool(m_Device, m_Handle, nullptr);
	}

	void CommandPool::CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateCommandPool(device, &info, nullptr, &m_Handle))
	}
}