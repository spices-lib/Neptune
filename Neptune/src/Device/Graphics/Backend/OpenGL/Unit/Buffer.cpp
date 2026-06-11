/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Buffer.h"

namespace Neptune::OpenGL::Unit {

	Buffer::~Buffer()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteBuffers(1, &m_Handle);
	}

	void Buffer::CreateBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		glGenBuffers(1, &m_Handle);
	}
}

#endif