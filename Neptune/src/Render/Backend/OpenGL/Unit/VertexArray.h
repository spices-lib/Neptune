/**
* @file VertexArray.h.
* @brief The VertexArray Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::VertexArray Class.
	* This class defines the OpenGL::Unit::VertexArray behaves.
	*/
	class VertexArray : public Unit<GLuint>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		VertexArray() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~VertexArray() override;

		/**
		* @brief Create VertexArray.
		*/
		void CreateVertexArray();

	};
}

#endif