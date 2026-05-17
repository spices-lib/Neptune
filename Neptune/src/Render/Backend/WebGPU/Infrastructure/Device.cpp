/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Device.h"
#include "Instance.h"
#include "Adapter.h"
#include "DebugUtilsObject.h"

namespace Neptune::WebGPU {

    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Device::Create()
    {
        NEPTUNE_PROFILE_ZONE

        m_Device.CreateDevice(GetContext().Get<IInstance>()->Handle(), GetContext().Get<IAdapter>()->Handle());
        
        DEBUGUTILS_SETOBJECTNAME(m_Device, ToString())
    }

    void Device::CreateBindGroup()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBindGroupDescriptor descriptor{};

        wgpuDeviceCreateBindGroup(m_Device.GetHandle(), &descriptor);
    }

    void Device::CreateBindGroupLayout()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBindGroupLayoutDescriptor desc{};

        wgpuDeviceCreateBindGroupLayout(m_Device.GetHandle(), &desc);
    }

    void Device::CreateBuffer()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBufferDescriptor desc{};

        wgpuDeviceCreateBuffer(m_Device.GetHandle(), &desc);
    }

    void Device::CreateCommandEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUCommandEncoderDescriptor desc{};

        wgpuDeviceCreateCommandEncoder(m_Device.GetHandle(), &desc);
    }

    void Device::CreateComputePipeline()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUComputePipelineDescriptor desc{};

        wgpuDeviceCreateComputePipeline(m_Device.GetHandle(), &desc);
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

        wgpuDeviceCreateComputePipelineAsync(m_Device.GetHandle(), &desc, info);
    }

    void Device::CreatePipelineLayout()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUPipelineLayoutDescriptor desc{};

        wgpuDeviceCreatePipelineLayout(m_Device.GetHandle(), &desc);
    }

    void Device::CreateQuerySet()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUQuerySetDescriptor desc{};

        wgpuDeviceCreateQuerySet(m_Device.GetHandle(), &desc);
    }

    void Device::CreateRenderBundleEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        WGPURenderBundleEncoderDescriptor desc{};

        wgpuDeviceCreateRenderBundleEncoder(m_Device.GetHandle(), &desc);
    }

    void Device::CreateRenderPipeline()
    {
        NEPTUNE_PROFILE_ZONE

        WGPURenderPipelineDescriptor desc{};

        wgpuDeviceCreateRenderPipeline(m_Device.GetHandle(), &desc);
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

        //Wait(wgpuDeviceCreateRenderPipelineAsync(m_Handle.GetHandle(), &desc, info));
    }

    void Device::CreateSampler()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSamplerDescriptor desc{};

        wgpuDeviceCreateSampler(m_Device.GetHandle(), &desc);
    }

    void Device::CreateShaderModule()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUShaderModuleDescriptor desc{};

        wgpuDeviceCreateShaderModule(m_Device.GetHandle(), &desc);
    }

    void Device::CreateTexture()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUTextureDescriptor desc{};

        wgpuDeviceCreateTexture(m_Device.GetHandle(), &desc);
    }

    void Device::Destroy()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuDeviceDestroy(m_Device.GetHandle());
    }

    void Device::GetAdapterInfo()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUAdapterInfo info{};

        wgpuDeviceGetAdapterInfo(m_Device.GetHandle(), &info);
    }

    void Device::GetFeatures()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedFeatures features{};

        wgpuDeviceGetFeatures(m_Device.GetHandle(), &features);
    }

    void Device::GetLimits()
    {
        NEPTUNE_PROFILE_ZONE

        WGPULimits limits{};

        wgpuDeviceGetLimits(m_Device.GetHandle(), &limits);
    }

    void Device::GetLostFuture()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuDeviceGetLostFuture(m_Device.GetHandle());
    }

    void Device::HasFeature()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuDeviceHasFeature(m_Device.GetHandle(), feature);
    }

    void Device::PopErrorScope()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUPopErrorScopeCallbackInfo info{};

        wgpuDevicePopErrorScope(m_Device.GetHandle(), info);
    }

    void Device::PushErrorScope()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUErrorFilter filter{};

        wgpuDevicePushErrorScope(m_Device.GetHandle(), filter);
    }

}

#endif