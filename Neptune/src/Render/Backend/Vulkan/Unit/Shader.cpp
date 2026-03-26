#include "Pchheader.h"
#include "Shader.h"
#include "..\..\..\..\Resource\Shader\Shader.h"

namespace Neptune::Vulkan::Unit {

	Shader::~Shader()
	{
		if (!m_Handle) return;

		vkDestroyShaderModule(m_Device, m_Handle, nullptr);
	}

	void Shader::CreateShader(VkDevice device, const VkShaderModuleCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateShaderModule(device, &info, nullptr, &m_Handle))
	}

}