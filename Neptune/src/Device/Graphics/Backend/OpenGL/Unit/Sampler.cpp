/**
* @file Sampler.cpp.
* @brief The Sampler Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Sampler.h"

namespace Neptune::OpenGL::Unit {

	Sampler::~Sampler()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteSamplers(1, &m_Handle);
	}

	void Sampler::CreateSampler()
	{
		NEPTUNE_PROFILE_ZONE

		glGenSamplers(1, &m_Handle);
	}
}

#endif