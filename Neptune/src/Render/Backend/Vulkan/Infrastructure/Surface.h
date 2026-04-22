/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Surface.h"
#include "Window/Enum.h"

namespace Neptune::Vulkan {

	using ISurface = IInfrastructure<class Surface, EInfrastructure::Surface>;

	/**
	* @brief Vulkan::Surface Class.
	* This class defines the Vulkan::Surface behaves.
	*/
	class Surface : public Infrastructure
	{
	public:

		static SP<Surface> Create(Context& context, EInfrastructure e, WindowImplement implement, void* window);

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Surface(Context& context, EInfrastructure e) : Infrastructure(context, e) {}
		
		/**
		* @brief Destructor Function.
		*/
		~Surface() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Surface::Handle& Handle() const { return m_Surface.GetHandle(); }

	protected:

		Unit::Surface m_Surface;         // @brief This Surface.

	};
	
}

#endif