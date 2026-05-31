/**
* @file FrameBuffer.cpp.
* @brief The FrameBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "FrameBuffer.h"

namespace Neptune::OpenGL::Unit {

	FrameBuffer::~FrameBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteFramebuffers(1, &m_Handle);
	}

	void FrameBuffer::CreateFrameBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		glGenFramebuffers(1, &m_Handle);
	}
}

#endif