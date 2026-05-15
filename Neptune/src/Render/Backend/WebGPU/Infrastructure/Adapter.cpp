/**
* @file Adapter.cpp.
* @brief The Adapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Adapter.h"
#include "Instance.h"

namespace Neptune::WebGPU {

    Adapter::Adapter(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Adapter::Create()
    {
        NEPTUNE_PROFILE_ZONE

        m_Adapter.CreateAdapter(GetContext().Get<IInstance>()->Handle());
    }

    void Adapter::GetFeatures()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSupportedFeatures features{};

        wgpuAdapterGetFeatures(m_Adapter.GetHandle(), &features);
    }

    void Adapter::GetInfo()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUAdapterInfo info{};

        WEBGPU_CHECK(wgpuAdapterGetInfo(m_Adapter.GetHandle(), &info))
    }

    void Adapter::GetLimits()
    {
        NEPTUNE_PROFILE_ZONE

        WGPULimits limits{};

        WEBGPU_CHECK(wgpuAdapterGetLimits(m_Adapter.GetHandle(), &limits))
    }

    void Adapter::HasFeature()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUFeatureName feature = WGPUFeatureName_CoreFeaturesAndLimits;

        wgpuAdapterHasFeature(m_Adapter.GetHandle(), feature);
    }

}

#endif