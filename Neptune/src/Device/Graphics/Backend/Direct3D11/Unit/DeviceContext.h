/**
* @file DeviceContext.h.
* @brief The DeviceContext Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::DeviceContext Class.
	* This class defines the Direct3D11::Unit::DeviceContext behaves.
	*/
	class DeviceContext : public Unit<D3D11DeviceContext>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		DeviceContext() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~DeviceContext() override;

	};
}

#endif