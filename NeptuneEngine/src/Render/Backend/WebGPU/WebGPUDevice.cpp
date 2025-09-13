/**
* @file WebGPUDevice.cpp.
* @brief The WebGPUDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUDevice.h"
#include "WebGPUAdapter.h"
#include "WebGPUInstance.h"

namespace Neptune {

    WebGPUDevice::WebGPUDevice(WebGPUContext& context)
        : WebGPUObject(context)
    {
        m_Device = m_Context.Get<WebGPUAdapter>()->RequestDevice();

        if (m_Device)
        {
            NEPTUNE_CORE_INFO("WGPUDevice created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUDevice created failed.")
        }
    }

    /*static void WebGPUErrorCallback(WGPUErrorType error_type, const char* message, void*)
    {
        const char* error_type_lbl = "";
        switch (error_type)
        {
            case WGPUErrorType_Validation:  error_type_lbl = "Validation"; break;
            case WGPUErrorType_OutOfMemory: error_type_lbl = "Out of memory"; break;
            case WGPUErrorType_Unknown:     error_type_lbl = "Unknown"; break;
            case WGPUErrorType_Internal:    error_type_lbl = "Internal"; break;
            case WGPUErrorType_Force32:     error_type_lbl = "Force32"; break;
            default:                        error_type_lbl = "Unknown";
        }

        std::stringstream ss;
        ss << error_type_lbl << "error: " << message;

        NEPTUNE_CORE_CRITICAL(ss.str())
    }
    */

    void WebGPUDevice::CreateBindGroup()
    {
        WGPUBindGroupDescriptor descriptor{};

        wgpuDeviceCreateBindGroup(m_Device, &descriptor);
    }

    void WebGPUDevice::CreateBindGroupLayout()
    {
        WGPUBindGroupLayoutDescriptor desc{};

        wgpuDeviceCreateBindGroupLayout(m_Device, &desc);
    }

    void WebGPUDevice::CreateBuffer()
    {
        WGPUBufferDescriptor desc{};

        wgpuDeviceCreateBuffer(m_Device, &desc);
    }

    void WebGPUDevice::CreateCommandEncoder()
    {
        WGPUCommandEncoderDescriptor desc{};

        wgpuDeviceCreateCommandEncoder(m_Device, &desc);
    }

    void WebGPUDevice::CreateComputePipeline()
    {
        WGPUComputePipelineDescriptor desc{};

        wgpuDeviceCreateComputePipeline(m_Device, &desc);
    }

    void WebGPUDevice::CreateComputePipelineAsync()
    {
        WGPUComputePipelineDescriptor desc{};

        static auto request = [](
            WGPUCreatePipelineAsyncStatus status    , 
            WGPUComputePipeline           pipeline  , 
            WGPUStringView                message   , 
            void*                         userdata1 , 
            void*
        ) {
        
        };

        WGPUCreateComputePipelineAsyncCallbackInfo   info{};
        info.mode                                  = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                             = nullptr;
        info.callback                              = request;

        wgpuDeviceCreateComputePipelineAsync(m_Device, &desc, info);
    }

    void WebGPUDevice::CreatePipelineLayout()
    {
        WGPUPipelineLayoutDescriptor desc{};

        wgpuDeviceCreatePipelineLayout(m_Device, &desc);
    }

    void WebGPUDevice::CreateQuerySet()
    {
        WGPUQuerySetDescriptor desc{};

        wgpuDeviceCreateQuerySet(m_Device, &desc);
    }

    void WebGPUDevice::CreateRenderBundleEncoder()
    {
        WGPURenderBundleEncoderDescriptor desc{};

        wgpuDeviceCreateRenderBundleEncoder(m_Device, &desc);
    }

    void WebGPUDevice::CreateRenderPipeline()
    {
        WGPURenderPipelineDescriptor desc{};

        wgpuDeviceCreateRenderPipeline(m_Device, &desc);
    }

    void WebGPUDevice::CreateRenderPipelineAsync()
    {
        WGPURenderPipelineDescriptor desc{};

        static auto request = [](
            WGPUCreatePipelineAsyncStatus status    ,
            WGPURenderPipeline            pipeline  ,
            WGPUStringView                message   , 
            void*                         userdata1 , 
            void*
        ) {
        
        };

        WGPUCreateRenderPipelineAsyncCallbackInfo    info{};
        info.mode                                  = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                             = nullptr;
        info.callback                              = request;

        Wait(wgpuDeviceCreateRenderPipelineAsync(m_Device, &desc, info));
    }

    void WebGPUDevice::CreateSampler()
    {
        WGPUSamplerDescriptor desc{};

        wgpuDeviceCreateSampler(m_Device, &desc);
    }

    void WebGPUDevice::CreateShaderModule()
    {
        WGPUShaderModuleDescriptor desc{};

        wgpuDeviceCreateShaderModule(m_Device, &desc);
    }

    void WebGPUDevice::CreateTexture()
    {
        WGPUTextureDescriptor desc{};

        wgpuDeviceCreateTexture(m_Device, &desc);
    }

    void WebGPUDevice::Destroy()
    {
        wgpuDeviceDestroy(m_Device);
    }

    void WebGPUDevice::GetAdapterInfo()
    {
        WGPUAdapterInfo info{};

        wgpuDeviceGetAdapterInfo(m_Device, &info);
    }

    void WebGPUDevice::GetFeatures()
    {
        WGPUSupportedFeatures features{};

        wgpuDeviceGetFeatures(m_Device, &features);
    }

    void WebGPUDevice::GetLimits()
    {
        WGPULimits limits{};

        wgpuDeviceGetLimits(m_Device, &limits);
    }

    void WebGPUDevice::GetLostFuture()
    {
        wgpuDeviceGetLostFuture(m_Device);
    }

    WGPUQueue WebGPUDevice::GetQueue()
    {
        return wgpuDeviceGetQueue(m_Device);
    }

    void WebGPUDevice::HasFeature()
    {
        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuDeviceHasFeature(m_Device, feature);
    }

    void WebGPUDevice::PopErrorScope()
    {
        WGPUPopErrorScopeCallbackInfo info{};

        wgpuDevicePopErrorScope(m_Device, info);
    }

    void WebGPUDevice::PushErrorScope()
    {
        WGPUErrorFilter filter{};

        wgpuDevicePushErrorScope(m_Device, filter);
    }

}

#endif