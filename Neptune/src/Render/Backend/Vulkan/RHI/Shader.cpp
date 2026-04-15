/**
* @file VertexBuffer.cpp.
* @brief The VertexBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Shader.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan {

	void Shader::SetSource(const std::vector<uint8_t>& source)
	{
		NEPTUNE_PROFILE_ZONE

		VkShaderModuleCreateInfo      info{};
		info.sType                  = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		info.codeSize               = source.size();
		info.pCode                  = reinterpret_cast<const uint32_t*>(source.data());

		m_Shader.CreateShader(GetContext().Get<IDevice>()->Handle(), info);
	}

	void Shader::SetName(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Shader,name)
	}
}

#endif