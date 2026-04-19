/**
* @file Heap.cpp.
* @brief The Heap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Heap.h"

namespace Neptune::Direct3D12::Unit {

	Heap::~Heap()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Heap::CreateHeap(D3D12Device device, const D3D12_HEAP_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateHeap(&desc, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif