/**
* @file RootSignature.cpp.
* @brief The RootSignature Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RootSignature.h"

namespace Neptune::Direct3D12::Unit {

	RootSignature::~RootSignature()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void RootSignature::CreateRootSignature(D3D12Device device, D3DBlob blob)
	{
		NEPTUNE_PROFILE_ZONE
		
		DIRECT3D12_CHECK(device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&m_Handle)))
	}

}

#endif