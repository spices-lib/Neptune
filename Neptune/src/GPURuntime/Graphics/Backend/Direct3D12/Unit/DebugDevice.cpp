/**
* @file DebugDevice.cpp.
* @brief The DebugDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DebugDevice.h"

namespace Neptune::Direct3D12::Unit {

	DebugDevice::~DebugDevice()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void DebugDevice::CreateDebugDevice(D3D12Device device)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->QueryInterface(IID_PPV_ARGS(&m_Handle)))
	}

}

#endif