/**
* @file Adapter.cpp.
* @brief The Adapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Adapter.h"
#include "Instance.h"
#include "Callback.h"

namespace Neptune::WebGPU {

    Adapter::Adapter(Context& context)
		: Infrastructure(context)
	{
        NEPTUNE_PROFILE_ZONE

        m_Handle = m_Context.Get<Instance>()->RequestAdapter();

        if (m_Handle)
        {
            NEPTUNE_CORE_INFO("WGPUAdapter created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUAdapter created failed.")
        }
    }

    void Adapter::GetFeatures()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedFeatures features{};

        wgpuAdapterGetFeatures(m_Handle, &features);
    }

    void Adapter::GetInfo()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUAdapterInfo info{};

        WEBGPU_CHECK(wgpuAdapterGetInfo(m_Handle, &info))
    }

    void Adapter::GetLimits()
    {
        NEPTUNE_PROFILE_ZONE

        WGPULimits limits{};

        WEBGPU_CHECK(wgpuAdapterGetLimits(m_Handle, &limits))
    }

    void Adapter::HasFeature()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuAdapterHasFeature(m_Handle, feature);
    }

    WGPUDevice Adapter::RequestDevice()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUDeviceLostCallbackInfo           deviceLostInfo{};
        deviceLostInfo.mode                = WGPUCallbackMode_WaitAnyOnly;
        deviceLostInfo.callback            = Callback::DeviceLostCallback;

        WGPUUncapturedErrorCallbackInfo      errorInfo{};
        errorInfo.callback                 = Callback::UncapturedErrorCallback;

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

        Wait(wgpuAdapterRequestDevice(m_Handle, &desc, info));

        return device;
    }

}

#endif