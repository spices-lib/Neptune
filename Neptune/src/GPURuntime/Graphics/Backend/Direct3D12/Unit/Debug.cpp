/**
* @file Debug.cpp.
* @brief The Debug Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Debug.h"

namespace Neptune::Direct3D12::Unit {

	Debug::~Debug()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Debug::CreateDebug()
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(D3D12GetDebugInterface(IID_PPV_ARGS(&m_Handle)))
	}

	void Debug::EnableDebugLayer() const
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle->EnableDebugLayer();

		m_Handle->SetEnableGPUBasedValidation(TRUE);
	}
}

#endif