#include "Pchheader.h"
#include "VideoSession.h"

namespace Neptune::Vulkan::Unit {

	VideoSession::~VideoSession()
	{
		if (!m_Handle) return;

		vkDestroyVideoSessionKHR(m_Device, m_Handle, nullptr);

		for (int i = 0 ; i < m_Memories.size(); i++)
		{
			vkFreeMemory(m_Device, m_Memories[i], nullptr);
		}
	}

	void VideoSession::SetFunctor(PFN_vkCreateVideoSessionKHR create, PFN_vkDestroyVideoSessionKHR destroy, PFN_vkBindVideoSessionMemoryKHR bind)
	{
		vkCreateVideoSessionKHR  = create;
		vkDestroyVideoSessionKHR = destroy;
		vkBindVideoSessionMemoryKHR = bind;
	}

	void VideoSession::CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo)
	{
		assert(device && !m_Handle);

		m_Device = device;

		VK_CHECK(vkCreateVideoSessionKHR(m_Device, &createInfo, nullptr, &m_Handle))
	}

	const VkDeviceMemory& VideoSession::AllocateMemory(const VkMemoryAllocateInfo& info)
	{
		VkDeviceMemory memory = VK_NULL_HANDLE;

		VK_CHECK(vkAllocateMemory(m_Device, &info, nullptr, &memory))

		m_Memories.emplace_back(memory);

		return memory;
	}

	void VideoSession::BindVideoSessionMemory(const std::vector<VkBindVideoSessionMemoryInfoKHR>& infos) const
	{
		VK_CHECK(vkBindVideoSessionMemoryKHR(m_Device, m_Handle, infos.size(), infos.data()))
	}
}