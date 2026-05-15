/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Surface.h"

namespace Neptune::Vulkan::GLFW {

	/**
	* @brief Vulkan::GLFW::Surface Class.
	* This class defines the Vulkan::GLFW::Surface behaves.
	*/
	class Surface : public Vulkan::Surface
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] window Native window.
		*/
		Surface(Context& context, EInfrastructure e, void* window);

		/**
		* @brief Destructor Function.
		*/
		~Surface() override = default;

	private:

		/**
		* @brief Create Surface.
		*
		* @param[in] window Native window.
		*/
		void Create(void* window);

	};
	
}

#endif