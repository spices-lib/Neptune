/**
* @file TransformFeedback.h.
* @brief The TransformFeedback Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::TransformFeedback Class.
	* This class defines the OpenGL::Unit::TransformFeedback behaves.
	*/
	class TransformFeedback : public Unit<GLuint>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		TransformFeedback() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~TransformFeedback() override;

		/**
		* @brief Create TransformFeedback.
		*/
		void CreateTransformFeedback();

	};
}

#endif