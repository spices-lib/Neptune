/**
* @file VertexArray.cpp.
* @brief The VertexArray Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Shader.h"

namespace Neptune::OpenGL::Unit {

	Shader::~Shader()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteShader(m_Handle);
	}

}

#endif