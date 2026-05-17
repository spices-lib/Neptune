/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Instance.h"
#include "DebugUtilsObject.h"

namespace Neptune::WebGPU {

    Instance::Instance(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Instance::Create()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUInstanceFeatureName                feature[1];
        feature[0]                           = WGPUInstanceFeatureName_TimedWaitAny;
                                             
        WGPUInstanceDescriptor                 descriptor{};
        descriptor.requiredFeatureCount      = 1;
        descriptor.requiredFeatures          = feature;

        m_Instance.CreateInstance(descriptor);
        
        DEBUGUTILS_SETOBJECTNAME(m_Instance, ToString())
    }

    void Instance::GetFeatures()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedInstanceFeatures features;

        wgpuGetInstanceFeatures(&features);
    }

    void Instance::GetLimits()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUInstanceLimits limit;

        WEBGPU_CHECK(wgpuGetInstanceLimits(&limit))
    }

    void Instance::HasFeature()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUInstanceFeatureName name = WGPUInstanceFeatureName_TimedWaitAny;

        wgpuHasInstanceFeature(name);
    }

    WGPUSurface Instance::CreateSurface(const std::string& htmlCanvas)
    {
        
    }

    void Instance::GetWGSLFeatures()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedWGSLLanguageFeatures features{};

        wgpuInstanceGetWGSLLanguageFeatures(m_Instance.GetHandle(), &features);
    }

    void Instance::HasWGSLFeature()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUWGSLLanguageFeatureName name = WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures;

        wgpuInstanceHasWGSLLanguageFeature(m_Instance.GetHandle(), name);
    }

    void Instance::ProcessEvents()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuInstanceProcessEvents(m_Instance.GetHandle());
    }

}

#endif