/**
* @file Program.h.
* @brief The Program Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::Program Class.
	* This class defines the OpenGL::Unit::Program behaves.
	*/
	class Program : public Unit<GLuint, GL_PROGRAM>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Program() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Program() override;

		/**
		* @brief Create Program.
		*/
		void CreateProgram();

	};
}

#endif