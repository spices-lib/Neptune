/**
* @file VertexArray.cpp.
* @brief The VertexArray Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "VertexArray.h"

namespace Neptune::OpenGL::Unit {

	VertexArray::~VertexArray()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteVertexArrays(1, &m_Handle);
	}

	void VertexArray::CreateVertexArray()
	{
		NEPTUNE_PROFILE_ZONE

		glGenVertexArrays(1, &m_Handle);
	}
}

#endif