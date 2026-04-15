/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/Utils.h"

#include <functional>
#include <glad/glad.h>

namespace Neptune::OpenGL {

	#define OPENGL_VERSION  4.6                                                // @brief Use OpenGL 4.6.

	/**
	* @brief OpenGLResult Delegate Class.
	*/
    struct HandleOpenGLResultDelegate
    {
        using Handler = std::function<void(GLenum)>;

		/**
		* @brief Set Handler.
		* 
		* @param[in] fn Handler.
		*/
        static void SetHandler(const Handler& fn);

		/**
		* @brief Get Handler.
		*
		* @return Returns Handler.
		*/
        static const Handler& GetHandler();
    };
	
	/**
	* @brief Handle OpenGLR Error Result.
	*
	* @param[in] result GLenum.
	*/
	void HandleOpenGLResult(GLenum result);

	#define OPENGL_CHECK(expr)  { auto expr_value = expr; if (expr_value != GL_NO_ERROR) { std::invoke(HandleOpenGLResultDelegate::GetHandler(), expr_value); } }
}

#endif