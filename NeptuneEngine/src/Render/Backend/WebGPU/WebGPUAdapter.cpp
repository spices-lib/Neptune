/**
* @file WebGPUAdapter.cpp.
* @brief The WebGPUAdapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUAdapter.h"
#include "WebGPUInstance.h"
#include "WebGPUCallback.h"

namespace Neptune {

	WebGPUAdapter::WebGPUAdapter(WebGPUContext& context)
		: WebGPUObject(context)
	{
        m_Adapter = m_Context.Get<WebGPUInstance>()->RequestAdapter();

        if (m_Adapter)
        {
            NEPTUNE_CORE_INFO("WGPUAdapter created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUAdapter created failed.")
        }
    }

    void WebGPUAdapter::GetFeatures() 
    {
        WGPUSupportedFeatures features{};

        wgpuAdapterGetFeatures(m_Adapter, &features);
    }

    void WebGPUAdapter::GetInfo() 
    {
        WGPUAdapterInfo info{};

        WEBGPU_CHECK(wgpuAdapterGetInfo(m_Adapter, &info))
    }

    void WebGPUAdapter::GetLimits() 
    {
        WGPULimits limits{};

        WEBGPU_CHECK(wgpuAdapterGetLimits(m_Adapter, &limits))
    }

    void WebGPUAdapter::HasFeature() 
    {
        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuAdapterHasFeature(m_Adapter, feature);
    }

    WGPUDevice WebGPUAdapter::RequestDevice()
    {
         WGPUDeviceLostCallbackInfo           deviceLostInfo{};
        deviceLostInfo.mode                = WGPUCallbackMode_WaitAnyOnly;
        deviceLostInfo.callback            = WebGPUCallback::WebGPUDeviceLostCallback;

        WGPUUncapturedErrorCallbackInfo      errorInfo{};
        errorInfo.callback                 = WebGPUCallback::WebGPUUncapturedErrorCallback;

        WGPUDeviceDescriptor                 desc{};
        desc.deviceLostCallbackInfo        = deviceLostInfo;
        desc.uncapturedErrorCallbackInfo   = errorInfo;

        WGPUDevice device = nullptr;

        static auto request = [](
            WGPURequestDeviceStatus  status,
            WGPUDevice               device,
            WGPUStringView           message,
            void* userdata1,
            void*
            ) {
                if (auto p = static_cast<WGPUDevice*>(userdata1))
                {
                    *p = device;
                }
        };

        WGPURequestDeviceCallbackInfo     info{};
        info.mode                       = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                  = &device;
        info.callback                   = request;

        Wait(wgpuAdapterRequestDevice(m_Adapter, &desc, info));

        return device;
    }

}

#endif