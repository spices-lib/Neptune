/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderPass.h"

namespace Neptune::Vulkan::Unit {

	RenderPass::~RenderPass()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyRenderPass(m_Device, m_Handle, nullptr);
	}

	void RenderPass::CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateRenderPass(device, &info, nullptr, &m_Handle))
	}
}

#endif