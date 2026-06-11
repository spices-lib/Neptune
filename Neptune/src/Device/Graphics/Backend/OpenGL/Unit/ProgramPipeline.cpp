/**
* @file ProgramPipeline.cpp.
* @brief The ProgramPipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

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