/**
* @file Program.cpp.
* @brief The Program Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Program.h"

namespace Neptune::OpenGL::Unit {

	Program::~Program()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteProgram(m_Handle);
	}

	void Program::CreateProgram()
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle = glCreateProgram();
	}
}

#endif