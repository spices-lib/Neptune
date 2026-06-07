/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Pipeline.h"

namespace Neptune::Vulkan::Unit {

	Pipeline::~Pipeline()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyPipeline(m_Device, m_Handle, nullptr);
	}

	void Pipeline::CreateGraphicPipeline(VkDevice device, const VkGraphicsPipelineCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &info, nullptr, &m_Handle))
	}

	void Pipeline::CreateComputePipeline(VkDevice device, const VkComputePipelineCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &info, nullptr, &m_Handle))
	}
}

#endif