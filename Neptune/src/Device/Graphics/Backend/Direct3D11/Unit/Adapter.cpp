/**
* @file Adapter.cpp.
* @brief The Adapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Adapter.h"

namespace Neptune::Direct3D11::Unit {

	Adapter::~Adapter()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Adapter::CreateAdapter(DXGIFactory factory)
	{
		NEPTUNE_PROFILE_ZONE

		DXGIAdapter adapter = nullptr;
		D3D_FEATURE_LEVEL level;
		
		// Get adapters in descending order of performance
		for (UINT i = 0; factory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			// Pick the first adapter that supports the minimum feature level.
			auto result = D3D11CreateDevice(
				adapter, 
				D3D_DRIVER_TYPE_UNKNOWN, 
				nullptr, 
				D3D11_CREATE_DEVICE_BGRA_SUPPORT, 
				&MinimumLevel, 
				1, 
				D3D11_SDK_VERSION,
				nullptr, 
				&level,
				nullptr
			);

			if (FAILED(result))
			{
				if (adapter) adapter->Release();

				continue;
			}
			
			m_Handle = adapter;

			break;
		}

		if (!m_Handle)
		{
			NEPTUNE_CORE_ERROR("Do not find a DXGIAdapter satisfied minimum requirements.")
		}
	}

}

#endif