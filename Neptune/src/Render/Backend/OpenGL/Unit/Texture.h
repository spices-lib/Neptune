/**
* @file Texture.h.
* @brief The Texture Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::Texture Class.
	* This class defines the OpenGL::Unit::Texture behaves.
	*/
	class Texture : public Unit<GLuint>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Texture() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Texture() override;

		/**
		* @brief Create Texture.
		*/
		void CreateTexture();

	};
}

#endif