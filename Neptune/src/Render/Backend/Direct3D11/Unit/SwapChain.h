/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::SwapChain Class.
	* This class defines the Direct3D11::Unit::SwapChain behaves.
	*/
	class SwapChain : public Unit<DXGISwapChain>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		SwapChain() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override;

		/**
		* @brief Create SwapChain.
		*
		* @param[in] factory DXGIFactory.
		* @param[in] device D3D11Device.
		* @param[in] desc DXGI_SWAP_CHAIN_DESC1.
		* @param[in] hwnd Window HWND.
		*/
		void CreateSwapChain(DXGIFactory factory, D3D11Device device, const DXGI_SWAP_CHAIN_DESC1& desc, HWND hwnd);

	};
}

#endif