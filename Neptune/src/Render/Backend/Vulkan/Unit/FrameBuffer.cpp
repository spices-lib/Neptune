/**
* @file FrameBuffer.cpp.
* @brief The FrameBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "FrameBuffer.h"

namespace Neptune::Vulkan::Unit {

	FrameBuffer::~FrameBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyFramebuffer(m_Device, m_Handle, nullptr);
	}

	void FrameBuffer::CreateFrameBuffer(VkDevice device, const VkFramebufferCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateFramebuffer(device, &info, nullptr, &m_Handle))
	}
}