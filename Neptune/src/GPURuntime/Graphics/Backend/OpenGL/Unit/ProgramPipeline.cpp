/**
* @file ProgramPipeline.cpp.
* @brief The ProgramPipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "ProgramPipeline.h"

namespace Neptune::OpenGL::Unit {

	ProgramPipeline::~ProgramPipeline()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteProgramPipelines(1, &m_Handle);
	}

	void ProgramPipeline::CreateProgramPipeline()
	{
		NEPTUNE_PROFILE_ZONE

		glGenProgramPipelines(1, &m_Handle);
	}
}

#endif