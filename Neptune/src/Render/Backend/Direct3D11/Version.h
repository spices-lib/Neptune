/**
* @file Version.h.
* @brief The Version Class Definitions.
* @author Spices.
*/

#pragma once
#include <d3d11_4.h>
#include <dxgi1_6.h>

#ifdef NP_PLATFORM_WINDOWS

namespace Neptune::Direct3D11 {
	
	using DXGIFactory              = IDXGIFactory7*;
	using DXGIAdapter              = IDXGIAdapter4*;
	using D3DBlob                  = ID3DBlob*;
	using DXGISwapChain            = IDXGISwapChain4*;

	using Device                   = ID3D11Device5*;
	using DeviceContext            = ID3D11DeviceContext4*;
	using RenderTargetView         = ID3D11RenderTargetView1*;
	using DepthStencilView         = ID3D11DepthStencilView*;
	using VertexShader             = ID3D11VertexShader*;
	using PixelShader              = ID3D11PixelShader*;
	using InputLayout              = ID3D11InputLayout*;
	using DepthStencilState        = ID3D11DepthStencilState*;
	using Texture2D                = ID3D11Texture2D1*;
	using Buffer                   = ID3D11Buffer*;
}

#endif