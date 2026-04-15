/**
* @file FrameBuffer.h.
* @brief The FrameBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::FrameBuffer Class.
	* This class defines the OpenGL::Unit::FrameBuffer behaves.
	*/
	class FrameBuffer : public Unit<GLuint>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		FrameBuffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~FrameBuffer() override;

		/**
		* @brief Create FrameBuffer.
		*/
		void CreateFrameBuffer();

	};
}

#endif