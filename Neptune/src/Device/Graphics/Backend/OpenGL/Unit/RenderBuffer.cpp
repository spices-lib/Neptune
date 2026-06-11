/**
* @file RenderBuffer.cpp.
* @brief The RenderBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "RenderBuffer.h"

namespace Neptune::OpenGL::Unit {

	RenderBuffer::~RenderBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteRenderbuffers(1, &m_Handle);
	}

	void RenderBuffer::CreateRenderBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		glGenRenderbuffers(1, &m_Handle);
	}
}

#endif