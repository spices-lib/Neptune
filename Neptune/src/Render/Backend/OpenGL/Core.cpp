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
	
		HandleOpenGLResultDelegate::Handler s_Handler;   // @brief HandleOpenGLResultDelegate::Handler instance.
	}

	void HandleOpenGLResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleOpenGLResultDelegate::Handler& HandleOpenGLResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void HandleOpenGLResult(GLenum result)
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
		ss << "OpenGL Error: [ " << label << " ]: ";

        NEPTUNE_CORE_ERROR(ss.str())
	}
}

#endif