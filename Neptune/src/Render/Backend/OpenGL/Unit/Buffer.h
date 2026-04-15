/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::Buffer Class.
	* This class defines the OpenGL::Unit::Buffer behaves.
	*/
	class Buffer : public Unit
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Buffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Buffer() override;

		/**
		* @brief Create Buffer.
		*/
		void CreateBuffer();

	};
}

#endif