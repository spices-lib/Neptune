/**
* @file Sampler.h.
* @brief The Sampler Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::Sampler Class.
	* This class defines the OpenGL::Unit::Sampler behaves.
	*/
	class Sampler : public Unit<GLuint, GL_SAMPLER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Sampler() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Sampler() override;

		/**
		* @brief Create Sampler.
		*/
		void CreateSampler();

	};
}

#endif