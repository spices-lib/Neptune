/**
* @file Version.h.
* @brief The Version Class Definitions.
* @author Spices.
*/

#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>

#ifdef NP_PLATFORM_WINDOWS

namespace Neptune::Direct3D12 {

	using D3D12Debug               = ID3D12Debug3*;
	using D3D12Device              = ID3D12Device14*;
	using DXGIFactory              = IDXGIFactory7*;
	using D3D12InfoQueue           = ID3D12InfoQueue1*;
	using D3D12DebugDevice         = ID3D12DebugDevice2*;
	using DXGIAdapter              = IDXGIAdapter4*;
	using D3D12DescriptorHeap      = ID3D12DescriptorHeap*;
	using D3D12CommandQueue        = ID3D12CommandQueue1*;
	using D3D12CommandAllocator    = ID3D12CommandAllocator*;
	using D3D12GraphicsCommandList = ID3D12GraphicsCommandList10*;
	using D3D12Fence               = ID3D12Fence1*;
	using D3D12Resource            = ID3D12Resource2*;
	using D3D12Heap                = ID3D12Heap1*;
	using D3D12RootSignature       = ID3D12RootSignature*;
	using D3D12PipelineState       = ID3D12PipelineState1*;
	using D3DBlob                  = ID3DBlob*;
	using DXGISwapChain            = IDXGISwapChain4*;

}

#endif