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
	* @brief OpenGL::Unit::Query Class.
	* This class defines the OpenGL::Unit::Query behaves.
	*/
	class Query : public Unit<GLuint>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Query() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Query() override;

		/**
		* @brief Create Query.
		*/
		void CreateQuery();

	};
}

#endif