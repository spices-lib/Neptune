/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Device.h"

namespace Neptune::WebGPU::Unit {

    Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

        wgpuDeviceRelease(m_Handle);
	}

	void Device::CreateDevice(WGPUInstance instance, WGPUAdapter adapter)
	{
		NEPTUNE_PROFILE_ZONE

		WGPUDeviceLostCallbackInfo                  deviceLostInfo{};
        deviceLostInfo.mode                       = WGPUCallbackMode_WaitAnyOnly;
        deviceLostInfo.callback                   = DeviceLostCallback;
                                                  
        WGPUUncapturedErrorCallbackInfo             errorInfo{};
        errorInfo.callback                        = UncapturedErrorCallback;
                                                  
        WGPUDeviceDescriptor                        desc{};
        desc.deviceLostCallbackInfo               = deviceLostInfo;
        desc.uncapturedErrorCallbackInfo          = errorInfo;

        static auto request = [](
            WGPURequestDeviceStatus  status    ,
            WGPUDevice               device    ,
            WGPUStringView           message   ,
            void*                    userdata1 ,
            void*
        ) {
            if (auto p = static_cast<WGPUDevice*>(userdata1))
            {
                *p = device;
            	return;
            }
        	
        	NEPTUNE_CORE_ERROR(message.data)
        };

        WGPURequestDeviceCallbackInfo               info{};
        info.mode                                 = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                            = &m_Handle;
        info.callback                             = request;

        auto future = wgpuAdapterRequestDevice(adapter, &desc, info);

        WGPUFutureWaitInfo                          waitInfo{};
        waitInfo.future                           = future;

        WEBGPU_WAIT_CHECK(wgpuInstanceWaitAny(instance, 1, &waitInfo, WaitTimeoutNS))
	}

}

#endif