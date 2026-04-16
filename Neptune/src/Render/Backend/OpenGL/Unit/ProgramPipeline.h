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
	* @brief OpenGL::Unit::ProgramPipeline Class.
	* This class defines the OpenGL::Unit::ProgramPipeline behaves.
	*/
	class ProgramPipeline : public Unit<GLuint, GL_PROGRAM_PIPELINE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		ProgramPipeline() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~ProgramPipeline() override;

		/**
		* @brief Create ProgramPipeline.
		*/
		void CreateProgramPipeline();

	};
}

#endif