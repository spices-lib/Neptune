/**
* @file Fence.cpp.
* @brief The Fence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Fence.h"

namespace Neptune::Direct3D12::Unit {

	Fence::~Fence()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Fence::CreateFence(D3D12Device device)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif