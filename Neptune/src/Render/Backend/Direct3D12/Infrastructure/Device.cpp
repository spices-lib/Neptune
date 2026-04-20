/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Device.h"
#include "DebugUtilsObject.h"
#include "Render/Backend/Direct3D12/Unit/Debug.h"
#include "Render/Backend/Direct3D12/Unit/Adapter.h"
#include "Render/Backend/Direct3D12/Unit/InfoQueue.h"
#include "Render/Backend/Direct3D12/Unit/DebugDevice.h"
#include "Factory.h"

namespace Neptune::Direct3D12 {

    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

#ifdef NEPTUNE_DEBUG

		{
			Unit::InfoQueue infoQueue;

			infoQueue.CreateInfoQueue(m_Device.GetHandle());

			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, false);
			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, false);
			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, false);
		}

		{
			Unit::DebugDevice debug;

			debug.CreateDebugDevice(m_Device.GetHandle());

			DIRECT3D12_CHECK(debug.GetHandle()->ReportLiveDeviceObjects(D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL))
		}

#endif

	}

	void Device::Create()
    {
		NEPTUNE_PROFILE_ZONE

#ifdef NEPTUNE_DEBUG

		Unit::Debug debug;

		debug.CreateDebug();

		debug.EnableDebugLayer();

#endif

		Unit::Adapter adapter;

		adapter.CreateAdapter(GetContext().Get<IFactory>()->Handle());

		m_Device.CreateDevice(adapter.GetHandle(), GetMaxFeatureLevel(adapter.GetHandle()));

#ifdef NEPTUNE_DEBUG

		Unit::InfoQueue infoQueue;

		infoQueue.CreateInfoQueue(m_Device.GetHandle());

		infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
		infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

#endif
		
    }

	D3D_FEATURE_LEVEL Device::GetMaxFeatureLevel(DXGIAdapter adapter) const
	{
		NEPTUNE_PROFILE_ZONE

		D3D12_FEATURE_DATA_FEATURE_LEVELS        level{};
		level.NumFeatureLevels                 = _countof(FeatureLevels);
		level.pFeatureLevelsRequested          = FeatureLevels;

		Unit::Device device;

		device.CreateDevice(adapter, MinimumLevel);

		DIRECT3D12_CHECK(device.GetHandle()->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &level, sizeof(level)))

		return level.MaxSupportedFeatureLevel;
	}

}

#endif