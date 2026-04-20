/**
* @file Adapter.cpp.
* @brief The Adapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Adapter.h"

namespace Neptune::Direct3D12::Unit {

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

		// Get adapters in descending order of performance
		for (UINT i = 0; factory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			// Pick the first adapter that supports the minimum feature level.
			auto result = D3D12CreateDevice(adapter, MinimumLevel, __uuidof(ID3D12Device), nullptr);

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