/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DebugUtilsObject.h"

namespace Neptune::OpenGL {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {

#ifdef NEPTUNE_DEBUG

		SetDebugContext();

#endif

	}

	void DebugUtilsObject::BeginLabel(GLuint id, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, id, static_cast<GLsizei>(caption.size()), caption.c_str());
	}

	void DebugUtilsObject::EndLabel() const
	{
		NEPTUNE_PROFILE_ZONE

		glPopDebugGroup();
	}

	void DebugUtilsObject::SetDebugContext() const
	{
		NEPTUNE_PROFILE_ZONE

		glDebugMessageCallback(DebugCallback, nullptr);

		glEnable(GL_DEBUG_OUTPUT);
	}
}

#endif