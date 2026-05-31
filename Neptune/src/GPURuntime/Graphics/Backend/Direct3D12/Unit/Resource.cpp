/**
* @file Resource.cpp.
* @brief The Resource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Resource.h"

namespace Neptune::Direct3D12::Unit {

	namespace {
		
		constexpr D3D12_HEAP_PROPERTIES s_DefaultHeap
		{
			D3D12_HEAP_TYPE_DEFAULT,
			D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			D3D12_MEMORY_POOL_UNKNOWN,
			0,
			0
		};
	}

	Resource::~Resource()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Resource::CreateCommittedResource(D3D12Device device, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, const D3D12_CLEAR_VALUE& clearValue)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateCommittedResource(&s_DefaultHeap, D3D12_HEAP_FLAG_NONE, &desc, state, &clearValue, IID_PPV_ARGS(&m_Handle)))
	}

	void Resource::CreatePlacedResource(D3D12Device device, D3D12Heap heap, UINT64 offset, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, const D3D12_CLEAR_VALUE& clearValue)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreatePlacedResource(heap, offset, &desc, state, &clearValue, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif