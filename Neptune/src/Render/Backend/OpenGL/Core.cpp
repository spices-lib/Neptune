/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core.h"

namespace Neptune::OpenGL {

	namespace {
	
		HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam
	) {
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
			case GL_DEBUG_TYPE_PUSH_GROUP: break;
			case GL_DEBUG_TYPE_POP_GROUP: break;
			default:
			{
				NEPTUNE_CORE_INFO(ss.str())
				break;
			}
		}
	}
	
	void HandleResult(GLenum result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == GL_NO_ERROR) return;

		const char* label = "";
		switch (result)
		{
			case GL_INVALID_ENUM:                                        label = "Invalid Enum";                        break;
			case GL_INVALID_VALUE:                                       label = "Invalid Value";                       break;
			case GL_INVALID_OPERATION:                                   label = "Invalid Operation";                   break;
			case GL_STACK_OVERFLOW:                                      label = "Stack OverFlow";                      break;
			case GL_STACK_UNDERFLOW:                                     label = "Stack UnderFlow";                     break;
			case GL_OUT_OF_MEMORY:                                       label = "Out of Memory";                       break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:                       label = "Invalid Framebuffer Operation";       break;
			case GL_CONTEXT_LOST:                                        label = "Context Lost";                        break;
			default:                                                     label = "Unknown Error";                       break;
		}

		std::stringstream ss;
		ss << "OpenGL Error: [ " << label << " ]";

        NEPTUNE_CORE_ERROR(ss.str())
	}
}

#endif