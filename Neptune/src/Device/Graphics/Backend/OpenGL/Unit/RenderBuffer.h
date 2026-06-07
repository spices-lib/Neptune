/**
* @file RenderBuffer.h.
* @brief The RenderBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::RenderBuffer Class.
	* This class defines the OpenGL::Unit::RenderBuffer behaves.
	*/
	class RenderBuffer : public Unit<GLuint, GL_RENDERBUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RenderBuffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~RenderBuffer() override;

		/**
		* @brief Create RenderBuffer.
		*/
		void CreateRenderBuffer();

	};
}

#endif