/**
* @file VideoSession.cpp.
* @brief The VideoSession Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "VideoSession.h"

namespace Neptune::Vulkan::Unit {

	VideoSession::~VideoSession()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyVideoSessionKHR(m_Device, m_Handle, nullptr);

		for (int i = 0 ; i < m_Memories.size(); i++)
		{
			vkFreeMemory(m_Device, m_Memories[i], nullptr);
		}
	}

	void VideoSession::SetFunctor(PFN_vkCreateVideoSessionKHR create, PFN_vkDestroyVideoSessionKHR destroy, PFN_vkBindVideoSessionMemoryKHR bind)
	{
		NEPTUNE_PROFILE_ZONE

		vkCreateVideoSessionKHR      = create;
		vkDestroyVideoSessionKHR     = destroy;
		vkBindVideoSessionMemoryKHR  = bind;
	}

	void VideoSession::CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device && !m_Handle);

		m_Device = device;

		VK_CHECK(vkCreateVideoSessionKHR(m_Device, &createInfo, nullptr, &m_Handle))
	}

	VkDeviceMemory VideoSession::AllocateMemory(const VkMemoryAllocateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		VkDeviceMemory memory = VK_NULL_HANDLE;

		VK_CHECK(vkAllocateMemory(m_Device, &info, nullptr, &memory))

		m_Memories.emplace_back(memory);

		return memory;
	}

	void VideoSession::BindVideoSessionMemory(const std::vector<VkBindVideoSessionMemoryInfoKHR>& infos) const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkBindVideoSessionMemoryKHR(m_Device, m_Handle, infos.size(), infos.data()))
	}
}

#endif