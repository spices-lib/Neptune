/**
* @file PipelineState.cpp.
* @brief The PipelineState Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "PipelineState.h"

namespace Neptune::Direct3D12::Unit {

	PipelineState::~PipelineState()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void PipelineState::CreatePipelineState(D3D12Device device, const D3D12_PIPELINE_STATE_STREAM_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreatePipelineState(&desc, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif