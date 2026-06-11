/**
* @file VertexArray.cpp.
* @brief The VertexArray Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Shader.h"

namespace Neptune::OpenGL::Unit {

	Shader::~Shader()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteShader(m_Handle);
	}

}

#endif