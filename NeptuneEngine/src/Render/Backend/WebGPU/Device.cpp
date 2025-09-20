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
        NEPTUNE_PROFILE_ZONE

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
        NEPTUNE_PROFILE_ZONE

        WGPUBindGroupDescriptor descriptor{};

        wgpuDeviceCreateBindGroup(m_Handle, &descriptor);
    }

    void Device::CreateBindGroupLayout()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBindGroupLayoutDescriptor desc{};

        wgpuDeviceCreateBindGroupLayout(m_Handle, &desc);
    }

    void Device::CreateBuffer()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBufferDescriptor desc{};

        wgpuDeviceCreateBuffer(m_Handle, &desc);
    }

    void Device::CreateCommandEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUCommandEncoderDescriptor desc{};

        wgpuDeviceCreateCommandEncoder(m_Handle, &desc);
    }

    void Device::CreateComputePipeline()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUComputePipelineDescriptor desc{};

        wgpuDeviceCreateComputePipeline(m_Handle, &desc);
    }

    void Device::CreateComputePipelineAsync()
    {
        NEPTUNE_PROFILE_ZONE

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
        NEPTUNE_PROFILE_ZONE

        WGPUPipelineLayoutDescriptor desc{};

        wgpuDeviceCreatePipelineLayout(m_Handle, &desc);
    }

    void Device::CreateQuerySet()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUQuerySetDescriptor desc{};

        wgpuDeviceCreateQuerySet(m_Handle, &desc);
    }

    void Device::CreateRenderBundleEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        WGPURenderBundleEncoderDescriptor desc{};

        wgpuDeviceCreateRenderBundleEncoder(m_Handle, &desc);
    }

    void Device::CreateRenderPipeline()
    {
        NEPTUNE_PROFILE_ZONE

        WGPURenderPipelineDescriptor desc{};

        wgpuDeviceCreateRenderPipeline(m_Handle, &desc);
    }

    void Device::CreateRenderPipelineAsync()
    {
        NEPTUNE_PROFILE_ZONE

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
        NEPTUNE_PROFILE_ZONE

        WGPUSamplerDescriptor desc{};

        wgpuDeviceCreateSampler(m_Handle, &desc);
    }

    void Device::CreateShaderModule()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUShaderModuleDescriptor desc{};

        wgpuDeviceCreateShaderModule(m_Handle, &desc);
    }

    void Device::CreateTexture()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUTextureDescriptor desc{};

        wgpuDeviceCreateTexture(m_Handle, &desc);
    }

    void Device::Destroy()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuDeviceDestroy(m_Handle);
    }

    void Device::GetAdapterInfo()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUAdapterInfo info{};

        wgpuDeviceGetAdapterInfo(m_Handle, &info);
    }

    void Device::GetFeatures()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedFeatures features{};

        wgpuDeviceGetFeatures(m_Handle, &features);
    }

    void Device::GetLimits()
    {
        NEPTUNE_PROFILE_ZONE

        WGPULimits limits{};

        wgpuDeviceGetLimits(m_Handle, &limits);
    }

    void Device::GetLostFuture()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuDeviceGetLostFuture(m_Handle);
    }

    WGPUQueue Device::GetQueue()
    {
        NEPTUNE_PROFILE_ZONE

        return wgpuDeviceGetQueue(m_Handle);
    }

    void Device::HasFeature()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuDeviceHasFeature(m_Handle, feature);
    }

    void Device::PopErrorScope()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUPopErrorScopeCallbackInfo info{};

        wgpuDevicePopErrorScope(m_Handle, info);
    }

    void Device::PushErrorScope()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUErrorFilter filter{};

        wgpuDevicePushErrorScope(m_Handle, filter);
    }

}

#endif