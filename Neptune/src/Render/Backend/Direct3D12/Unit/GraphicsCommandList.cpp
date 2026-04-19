/**
* @file GraphicsCommandList.cpp.
* @brief The GraphicsCommandList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "GraphicsCommandList.h"

namespace Neptune::Direct3D12::Unit {

	GraphicsCommandList::~GraphicsCommandList()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void GraphicsCommandList::CreateGraphicsCommandList(D3D12Device device, D3D12CommandAllocator allocator, D3D12_COMMAND_LIST_TYPE type)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateCommandList(0, type, allocator, nullptr, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif