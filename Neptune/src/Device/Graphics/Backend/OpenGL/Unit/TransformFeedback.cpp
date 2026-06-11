/**
* @file TransformFeedback.cpp.
* @brief The TransformFeedback Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

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