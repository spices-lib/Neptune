/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

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