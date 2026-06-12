/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Device.h"

namespace Neptune::Direct3D12::Unit {

	Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Device::CreateDevice(DXGIAdapter adapter, D3D_FEATURE_LEVEL level)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(D3D12CreateDevice(adapter, level, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif