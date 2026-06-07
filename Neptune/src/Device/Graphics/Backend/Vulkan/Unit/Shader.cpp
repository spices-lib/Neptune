/**
* @file Shader.cpp.
* @brief The Shader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Shader.h"

namespace Neptune::Vulkan::Unit {

	Shader::~Shader()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyShaderModule(m_Device, m_Handle, nullptr);
	}

	void Shader::CreateShader(VkDevice device, const VkShaderModuleCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateShaderModule(device, &info, nullptr, &m_Handle))
	}

}

#endif