/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Instance.h"

namespace Neptune::WebGPU {

    Instance::Instance(Context& context)
            : Infrastructure(context)
    {
        Create();
    }

    void Instance::Create()
    {
        WGPUInstanceFeatureName             feature[1];
        feature[0]                        = WGPUInstanceFeatureName_TimedWaitAny;

        WGPUInstanceDescriptor              descriptor{};
        descriptor.requiredFeatureCount   = 1;
        descriptor.requiredFeatures       = feature;

        m_Handle = wgpuCreateInstance(&descriptor);

        if (m_Handle)
        {
            NEPTUNE_CORE_INFO("WGPUInstance created succeed.")
        }
        else 
        {
            NEPTUNE_CORE_CRITICAL("WGPUInstance created failed.")
        }
    }

    void Instance::GetFeatures()
    {
        WGPUSupportedInstanceFeatures features;

        wgpuGetInstanceFeatures(&features);
    }

    void Instance::GetLimits()
    {
        WGPUInstanceLimits limit;

        WEBGPU_CHECK(wgpuGetInstanceLimits(&limit))
    }

    void Instance::HasFeature()
    {
        WGPUInstanceFeatureName name = WGPUInstanceFeatureName_TimedWaitAny;

        wgpuHasInstanceFeature(name);
    }

    WGPUSurface Instance::CreateSurface(const std::string& htmlCanvas)
    {
        WGPUEmscriptenSurfaceSourceCanvasHTMLSelector                 htmlSelector  = {};
        htmlSelector.chain.sType                                    = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
        htmlSelector.chain.next                                     = nullptr;
        htmlSelector.selector                                       = { htmlCanvas.c_str()};

        WGPUSurfaceDescriptor                                         desc = {};
        desc.nextInChain                                            = &htmlSelector.chain;

        return wgpuInstanceCreateSurface(m_Handle, &desc);
    }

    void Instance::GetWGSLFeatures()
    {
        WGPUSupportedWGSLLanguageFeatures features{};

        wgpuInstanceGetWGSLLanguageFeatures(m_Handle, &features);
    }

    void Instance::HasWGSLFeature()
    {
        WGPUWGSLLanguageFeatureName name = WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures;

        wgpuInstanceHasWGSLLanguageFeature(m_Handle, name);
    }

    void Instance::ProcessEvents()
    {
        wgpuInstanceProcessEvents(m_Handle);
    }

    WGPUAdapter Instance::RequestAdapter()
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

        Wait(wgpuInstanceRequestAdapter(m_Handle, &options, info));

        return adaptor;
    }

    void Instance::Wait()
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

        WEBGPU_WAITCHECK(wgpuInstanceWaitAny(m_Handle, infos.size(), infos.data(), WaitTimeoutNS))
    }

    void Instance::Wait(const WGPUFuture& future)
    {
        WGPUFutureWaitInfo info{};
        info.future = future;

        WEBGPU_WAITCHECK(wgpuInstanceWaitAny(m_Handle, 1, &info, WaitTimeoutNS))
    }

    void Instance::PushToFutureList(const WGPUFuture& future)
    {
        m_FutureList.push_back(future);
    }

}

#endif