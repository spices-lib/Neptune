/**
* @file DescriptorHeap.cpp.
* @brief The DescriptorHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DescriptorHeap.h"

namespace Neptune::Direct3D12::Unit {

	DescriptorHeap::~DescriptorHeap()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void DescriptorHeap::CreateDescriptorHeap(D3D12Device device, const D3D12_DESCRIPTOR_HEAP_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif