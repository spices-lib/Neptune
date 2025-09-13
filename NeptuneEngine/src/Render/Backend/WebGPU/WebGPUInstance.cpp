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
            : WebGPUObject(context)
    {
        Create();
    }

    void WebGPUInstance::Create()
    {
        WGPUInstanceFeatureName             feature[1];
        feature[0]                        = WGPUInstanceFeatureName_TimedWaitAny;

        WGPUInstanceDescriptor              descriptor{};
        descriptor.requiredFeatureCount   = 1;
        descriptor.requiredFeatures       = feature;

        m_Instance = wgpuCreateInstance(&descriptor);

        if (m_Instance) 
        {
            NEPTUNE_CORE_INFO("WGPUInstance created succeed.")
        }
        else 
        {
            NEPTUNE_CORE_CRITICAL("WGPUInstance created failed.")
        }
    }

    void WebGPUInstance::GetFeatures() 
    {
        WGPUSupportedInstanceFeatures features;

        wgpuGetInstanceFeatures(&features);
    }

    void WebGPUInstance::GetLimits() 
    {
        WGPUInstanceLimits limit;

        WEBGPU_CHECK(wgpuGetInstanceLimits(&limit))
    }

    void WebGPUInstance::HasFeature() 
    {
        WGPUInstanceFeatureName name = WGPUInstanceFeatureName_TimedWaitAny;

        wgpuHasInstanceFeature(name);
    }

    WGPUSurface WebGPUInstance::CreateSurface(const std::string& htmlCanvas)
    {
        WGPUEmscriptenSurfaceSourceCanvasHTMLSelector                 htmlSelector  = {};
        htmlSelector.chain.sType                                    = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
        htmlSelector.chain.next                                     = nullptr;
        htmlSelector.selector                                       = { htmlCanvas.c_str()};

        WGPUSurfaceDescriptor                                         desc = {};
        desc.nextInChain                                            = &htmlSelector.chain;

        return wgpuInstanceCreateSurface(m_Instance, &desc);
    }

    void WebGPUInstance::GetWGSLFeatures() 
    {
        WGPUSupportedWGSLLanguageFeatures features{};

        wgpuInstanceGetWGSLLanguageFeatures(m_Instance, &features);
    }

    void WebGPUInstance::HasWGSLFeature() 
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

        Wait(wgpuInstanceRequestAdapter(m_Instance, &options, info));

        return adaptor;
    }

    void WebGPUInstance::Wait() 
    {
        if (m_FutureList.empty())
        {
            return;
        }

        std::vector<WGPUFutureWaitInfo> infos(m_FutureList.size());

        for (int i = 0; i < m_FutureList.size(); i++)
        {
            infos[i].future = m_FutureList[i];
        }

        WEBGPU_WAITCHECK(wgpuInstanceWaitAny(m_Instance, infos.size(), infos.data(), WaitTimeoutNS))
    }

    void WebGPUInstance::Wait(const WGPUFuture& future)
    {
        WGPUFutureWaitInfo info{};
        info.future = future;

        WEBGPU_WAITCHECK(wgpuInstanceWaitAny(m_Instance, 1, &info, WaitTimeoutNS))
    }

    void WebGPUInstance::PushToFutureList(const WGPUFuture& future)
    {
        m_FutureList.push_back(future);
    }

}

#endif