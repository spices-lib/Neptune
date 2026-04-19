/**
* @file CommandQueue.cpp.
* @brief The CommandQueue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandQueue.h"

namespace Neptune::Direct3D12::Unit {

	CommandQueue::~CommandQueue()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void CommandQueue::CreateCommandQueue(D3D12Device device, const D3D12_COMMAND_QUEUE_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif