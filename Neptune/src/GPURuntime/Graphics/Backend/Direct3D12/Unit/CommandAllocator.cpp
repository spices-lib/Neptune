/**
* @file CommandAllocator.cpp.
* @brief The CommandAllocator Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandAllocator.h"

namespace Neptune::Direct3D12::Unit {

	CommandAllocator::~CommandAllocator()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void CommandAllocator::CreateCommandAllocator(D3D12Device device, D3D12_COMMAND_LIST_TYPE type)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateCommandAllocator(type, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif