/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Surface.h"

namespace Neptune::Vulkan {

	using ISurface = InfrastructureClass<class Surface, EInfrastructure::Surface>;

	/**
	* @brief Vulkan::Surface Class.
	* This class defines the Vulkan::Surface behaves.
	*/
	class Surface : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count Semaphore Count.
		*/
		Surface(Context& context, EInfrastructure e);

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

	private:

		/**
		* @brief Create Surface.
		*/
		void Create();

	private:

		Unit::Surface m_Surface;         // @brief This Surface.

	};
	
}