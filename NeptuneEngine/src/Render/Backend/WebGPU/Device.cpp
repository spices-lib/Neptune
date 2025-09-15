/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Device.h"
#include "Adapter.h"
#include "Instance.h"

namespace Neptune::WebGPU {

    Device::Device(Context& context)
        : Infrastructure(context)
    {
        m_Handle = m_Context.Get<Adapter>()->RequestDevice();

        if (m_Handle)
        {
            NEPTUNE_CORE_INFO("WGPUDevice created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUDevice created failed.")
        }
    }

    void Device::CreateBindGroup()
    {
        WGPUBindGroupDescriptor descriptor{};

        wgpuDeviceCreateBindGroup(m_Handle, &descriptor);
    }

    void Device::CreateBindGroupLayout()
    {
        WGPUBindGroupLayoutDescriptor desc{};

        wgpuDeviceCreateBindGroupLayout(m_Handle, &desc);
    }

    void Device::CreateBuffer()
    {
        WGPUBufferDescriptor desc{};

        wgpuDeviceCreateBuffer(m_Handle, &desc);
    }

    void Device::CreateCommandEncoder()
    {
        WGPUCommandEncoderDescriptor desc{};

        wgpuDeviceCreateCommandEncoder(m_Handle, &desc);
    }

    void Device::CreateComputePipeline()
    {
        WGPUComputePipelineDescriptor desc{};

        wgpuDeviceCreateComputePipeline(m_Handle, &desc);
    }

    void Device::CreateComputePipelineAsync()
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

        wgpuDeviceCreateComputePipelineAsync(m_Handle, &desc, info);
    }

    void Device::CreatePipelineLayout()
    {
        WGPUPipelineLayoutDescriptor desc{};

        wgpuDeviceCreatePipelineLayout(m_Handle, &desc);
    }

    void Device::CreateQuerySet()
    {
        WGPUQuerySetDescriptor desc{};

        wgpuDeviceCreateQuerySet(m_Handle, &desc);
    }

    void Device::CreateRenderBundleEncoder()
    {
        WGPURenderBundleEncoderDescriptor desc{};

        wgpuDeviceCreateRenderBundleEncoder(m_Handle, &desc);
    }

    void Device::CreateRenderPipeline()
    {
        WGPURenderPipelineDescriptor desc{};

        wgpuDeviceCreateRenderPipeline(m_Handle, &desc);
    }

    void Device::CreateRenderPipelineAsync()
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

        Wait(wgpuDeviceCreateRenderPipelineAsync(m_Handle, &desc, info));
    }

    void Device::CreateSampler()
    {
        WGPUSamplerDescriptor desc{};

        wgpuDeviceCreateSampler(m_Handle, &desc);
    }

    void Device::CreateShaderModule()
    {
        WGPUShaderModuleDescriptor desc{};

        wgpuDeviceCreateShaderModule(m_Handle, &desc);
    }

    void Device::CreateTexture()
    {
        WGPUTextureDescriptor desc{};

        wgpuDeviceCreateTexture(m_Handle, &desc);
    }

    void Device::Destroy()
    {
        wgpuDeviceDestroy(m_Handle);
    }

    void Device::GetAdapterInfo()
    {
        WGPUAdapterInfo info{};

        wgpuDeviceGetAdapterInfo(m_Handle, &info);
    }

    void Device::GetFeatures()
    {
        WGPUSupportedFeatures features{};

        wgpuDeviceGetFeatures(m_Handle, &features);
    }

    void Device::GetLimits()
    {
        WGPULimits limits{};

        wgpuDeviceGetLimits(m_Handle, &limits);
    }

    void Device::GetLostFuture()
    {
        wgpuDeviceGetLostFuture(m_Handle);
    }

    WGPUQueue Device::GetQueue()
    {
        return wgpuDeviceGetQueue(m_Handle);
    }

    void Device::HasFeature()
    {
        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuDeviceHasFeature(m_Handle, feature);
    }

    void Device::PopErrorScope()
    {
        WGPUPopErrorScopeCallbackInfo info{};

        wgpuDevicePopErrorScope(m_Handle, info);
    }

    void Device::PushErrorScope()
    {
        WGPUErrorFilter filter{};

        wgpuDevicePushErrorScope(m_Handle, filter);
    }

}

#endif