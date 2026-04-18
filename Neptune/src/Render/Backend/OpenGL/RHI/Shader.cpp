/**
* @file VertexBuffer.cpp.
* @brief The VertexBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Shader.h"
#include "Render/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

namespace Neptune::OpenGL {

	void Shader::SetSource(const std::vector<uint8_t>& source)
	{
		NEPTUNE_PROFILE_ZONE
	}

	void Shader::SetName(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Shader, name)
	}
}

#endif