/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Device.h"
#include "DebugUtilsObject.h"
#include "Factory.h"
#include "DeviceContext.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/Adapter.h"
#include "Core/Library/StringLibrary.h"

namespace Neptune::Direct3D11 {
	
    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	void Device::Create()
    {
		NEPTUNE_PROFILE_ZONE

		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    	D3D_DRIVER_TYPE drivenType = D3D_DRIVER_TYPE_UNKNOWN;
    	
#ifdef NEPTUNE_DEBUG

		flags |= D3D11_CREATE_DEVICE_DEBUG;
    	
#endif

		Unit::Adapter adapter;

		adapter.CreateAdapter(GetContext().Get<IFactory>()->Handle());

    	Unit::DeviceContext::Handle deviceContext;
    	
		m_Device.CreateDevice(adapter.GetHandle(), drivenType, flags, MinimumLevel, deviceContext);
    	
    	DEBUGUTILS_SETOBJECTNAME(m_Device, ToString())
    	
    	GetContext().Get<IDeviceContext>()->SetHandle(deviceContext);
    	
    	GetContext().Get<IDebugUtilsObject>()->Create();
    	
    	DXGI_ADAPTER_DESC3 desc{};
    	adapter.GetHandle()->GetDesc3(&desc);
    	
    	std::stringstream ss;
    	ss << "D3D11 Device Selected: " << StringLibrary::WCharToChar(desc.Description);
    	
    	NEPTUNE_CORE_INFO(ss.str())
    }

}

#endif