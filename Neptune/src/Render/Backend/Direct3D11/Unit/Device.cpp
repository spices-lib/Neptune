/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Device.h"

namespace Neptune::Direct3D11::Unit {

	Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Device::CreateDevice(DXGIAdapter adapter, D3D_DRIVER_TYPE drivenType, UINT flags, D3D_FEATURE_LEVEL level, D3D11DeviceContext& context)
	{
		NEPTUNE_PROFILE_ZONE

		D3D_FEATURE_LEVEL supportLevel;
		
		ID3D11Device* baseDevice;
		ID3D11DeviceContext* baseContext;
		
		DIRECT3D11_CHECK(D3D11CreateDevice(adapter, drivenType, nullptr, flags, &level, 1, D3D11_SDK_VERSION, &baseDevice, &supportLevel, &baseContext))
		
		m_Handle = dynamic_cast<Handle>(baseDevice);
		context  = dynamic_cast<D3D11DeviceContext>(baseContext);
	}

}

#endif