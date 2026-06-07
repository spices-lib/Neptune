/**
* @file TransformFeedback.cpp.
* @brief The TransformFeedback Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "TransformFeedback.h"

namespace Neptune::OpenGL::Unit {

	TransformFeedback::~TransformFeedback()
	{
		NEPTUNE_PROFILE_ZONE

		glDeleteTransformFeedbacks(1, &m_Handle);
	}

	void TransformFeedback::CreateTransformFeedback()
	{
		NEPTUNE_PROFILE_ZONE

		glGenTransformFeedbacks(1, &m_Handle);
	}
}

#endif