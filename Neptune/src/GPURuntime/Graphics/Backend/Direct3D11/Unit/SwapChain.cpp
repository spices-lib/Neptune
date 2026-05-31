/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "SwapChain.h"

namespace Neptune::Direct3D11::Unit {

	SwapChain::~SwapChain()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void SwapChain::CreateSwapChain(DXGIFactory factory, D3D11Device device, const DXGI_SWAP_CHAIN_DESC1& desc, HWND hwnd)
	{
		NEPTUNE_PROFILE_ZONE

		IDXGISwapChain1* swapChain = nullptr;

		DIRECT3D11_CHECK(factory->CreateSwapChainForHwnd(device, hwnd, &desc, nullptr, nullptr, &swapChain))

		DIRECT3D11_CHECK(factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER))

		DIRECT3D11_CHECK(swapChain->QueryInterface(IID_PPV_ARGS(&m_Handle)))

		if (!swapChain) return;

		swapChain->Release();
	}

}

#endif