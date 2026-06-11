/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::Device Class.
	* This class defines the Direct3D11::Unit::Device behaves.
	*/
	class Device : public Unit<D3D11Device>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Device() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Device() override;

		/**
		* @brief Create Device.
		* 
		* @param[in] adapter DXGIAdapter.
		* @param[in] drivenType D3D_DRIVER_TYPE.
		* @param[in] flags Create Flags.
		* @param[in] level D3D_FEATURE_LEVEL.
		* @param[in] context D3D11DeviceContext.
		*/
		void CreateDevice(DXGIAdapter adapter, D3D_DRIVER_TYPE drivenType, UINT flags, D3D_FEATURE_LEVEL level, D3D11DeviceContext& context);

	};
}

#endif