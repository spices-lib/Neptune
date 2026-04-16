/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DebugUtilsObject.h"

namespace Neptune::OpenGL {

	namespace {
	
		/**
		* @brief Debug Callback Functor.
		*
		* @param[in] source Message Source.
		* @param[in] type Message Type.
		* @param[in] id Message unique id.
		* @param[in] severity Message Level.
		* @param[in] length Message bytes.
		* @param[in] message Message data.
		* @param[im] userParam Callback.
		*/
		void GLAPIENTRY InstanceDebugCallback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length, const GLchar* message, const void* userParam
		){
			NEPTUNE_PROFILE_ZONE

			std::stringstream ss;

			ss <<
			"OpenGL Validation:\n			" <<
			"MessageIdNumber: " << id <<
			"\n			MessageIdName: " << source;
			ss << "\n			Message: " << message;

			switch (type)
			{
				case GL_DEBUG_SEVERITY_NOTIFICATION:
				{
					NEPTUNE_CORE_TRACE(ss.str())
					break;
				}
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				case GL_DEBUG_TYPE_PORTABILITY:
				case GL_DEBUG_TYPE_PERFORMANCE:
				{
					NEPTUNE_CORE_WARN(ss.str())
					break;
				}
				case GL_DEBUG_TYPE_ERROR:
				{
					NEPTUNE_CORE_ERROR(ss.str())
					break;
				}
				default:
				{
					NEPTUNE_CORE_INFO(ss.str())
					break;
				}
			}
		}
	}

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

		glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, id, caption.size(), caption.c_str());
	}

	void DebugUtilsObject::EndLabel() const
	{
		NEPTUNE_PROFILE_ZONE

		glPopDebugGroup();
	}

	void DebugUtilsObject::SetDebugContext() const
	{
		NEPTUNE_PROFILE_ZONE

		glDebugMessageCallback(InstanceDebugCallback, nullptr);

		glEnable(GL_DEBUG_OUTPUT);
	}
}

#endif