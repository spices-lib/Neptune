/**
* @file WebGPUInstance.cpp.
* @brief The WebGPUInstance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUInstance.h"

namespace Neptune {

    WebGPUInstance::WebGPUInstance(WebGPUContext& context)
            : WebGPUObject(context, EWebGPUObject::WebGPUInstance)
    {
        CreateInstance();
    }

    WebGPUInstance::~WebGPUInstance()
    {
        Release();
    }

    void WebGPUInstance::CreateInstance()
    {
        WGPUInstanceFeatureName             feature[1];
        feature[0]                        = WGPUInstanceFeatureName_TimedWaitAny;

        WGPUInstanceDescriptor              descriptor{};
        descriptor.requiredFeatureCount   = 1;
        descriptor.requiredFeatures       = feature;

        m_Instance = wgpuCreateInstance(&descriptor);

        if (!m_Instance) 
        {
            NEPTUNE_CORE_CRITICAL("WGPUInstance created failed.")
        }
    }

    void WebGPUInstance::GetInstanceFeatures() 
    {
        WGPUSupportedInstanceFeatures features;

        wgpuGetInstanceFeatures(&features);
    }

    void WebGPUInstance::GetInstanceLimits() 
    {
        WGPUInstanceLimits limit;

        WEBGPU_CHECK(wgpuGetInstanceLimits(&limit))
    }

    void WebGPUInstance::HasInstanceFeature() 
    {
        WGPUInstanceFeatureName name = WGPUInstanceFeatureName_TimedWaitAny;

        wgpuHasInstanceFeature(name);
    }

    void WebGPUInstance::CreateSurface() 
    {
        WGPUSurfaceDescriptor descriptor{};

        wgpuInstanceCreateSurface(m_Instance, &descriptor);
    }

    void WebGPUInstance::GetWGSLLanguageFeatures() 
    {
        WGPUSupportedWGSLLanguageFeatures features{};

        wgpuInstanceGetWGSLLanguageFeatures(m_Instance, &features);
    }

    void WebGPUInstance::HasWGSLLanguageFeature() 
    {
        WGPUWGSLLanguageFeatureName name = WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures;

        wgpuInstanceHasWGSLLanguageFeature(m_Instance, name);
    }

    void WebGPUInstance::ProcessEvents() 
    {
        wgpuInstanceProcessEvents(m_Instance);
    }

    WGPUAdapter WebGPUInstance::RequestAdapter()
    {
        WGPURequestAdapterOptions options{};

        WGPUAdapter adaptor = nullptr;

        static auto request = [](
            WGPURequestAdapterStatus status, 
            WGPUAdapter              adapter  , 
            WGPUStringView           message  , 
            void*                    userdata1, 
            void*
        ) {
            if (auto p = static_cast<WGPUAdapter*>(userdata1)) 
            {
                *p = adapter;
            }
        };

        WGPURequestAdapterCallbackInfo    info{};
        info.mode                       = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                  = &adaptor;
        info.callback                   = request;

        PushToFutureList(wgpuInstanceRequestAdapter(m_Instance, &options, info));

        WaitAny();

        return adaptor;
    }

    void WebGPUInstance::WaitAny() 
    {
        if (m_Future.empty())
        {
            return;
        }

        std::vector<WGPUFutureWaitInfo> infos(m_Future.size());

        for (int i = 0; i < m_Future.size(); i++)
        {
            infos[i].future = m_Future[i];
        }

        WEBGPU_WAITCHECK(wgpuInstanceWaitAny(m_Instance, infos.size(), infos.data(), WaitTimeoutNS))
    }

    void WebGPUInstance::AddRef() 
    {
        wgpuInstanceAddRef(m_Instance);
    }

    void WebGPUInstance::Release() 
    {
        if (!m_Instance)
        {
            return;
        }

        wgpuInstanceRelease(m_Instance);
        m_Instance = nullptr;
    }

    void WebGPUInstance::PushToFutureList(const WGPUFuture& future)
    {
        m_Future.push_back(future);
    }

}

#endif