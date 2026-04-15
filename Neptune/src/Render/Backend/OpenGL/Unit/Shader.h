/**
* @file Shader.h.
* @brief The Shader Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::OpenGL::Unit {

	/**
	* @brief OpenGL::Unit::Shader Class.
	* This class defines the OpenGL::Unit::Shader behaves.
	*/
	class Shader : public Unit
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Shader() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Shader() override;

		/**
		* @brief Create Shader.
		* 
		* @param[in] type Shader Type.
		*/
		template<typename T>
		void CreateShader(T&& type)
		{
			NEPTUNE_PROFILE_ZONE

			m_Handle = glCreateShader(type);
		}

	};
}

#endif