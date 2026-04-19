/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "SwapChain.h"

namespace Neptune::Direct3D12::Unit {

	SwapChain::~SwapChain()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void SwapChain::CreateSwapChain(DXGIFactory factory, D3D12CommandQueue commandQueue, const DXGI_SWAP_CHAIN_DESC1& desc)
	{
		NEPTUNE_PROFILE_ZONE

		HWND hwnd{}; //= (HWND)_window.handle() };

		IDXGISwapChain1* swapChain = nullptr;

		DIRECT3D12_CHECK(factory->CreateSwapChainForHwnd(commandQueue, hwnd, &desc, nullptr, nullptr, &swapChain))

		DIRECT3D12_CHECK(swapChain->QueryInterface(IID_PPV_ARGS(&m_Handle)))

		if (!swapChain) return;

		swapChain->Release();
	}

}

#endif