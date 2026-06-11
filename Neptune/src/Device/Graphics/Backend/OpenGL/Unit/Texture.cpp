/**
* @file Texture.cpp.
* @brief The Texture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Texture.h"

namespace Neptune::OpenGL::Unit {

	Texture::~Texture()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteTextures(1, &m_Handle);
	}

	void Texture::CreateTexture()
	{
		NEPTUNE_PROFILE_ZONE

		glGenTextures(1, &m_Handle);
	}
}

#endif