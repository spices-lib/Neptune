/**
* @file Adapter.cpp.
* @brief The Adapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Adapter.h"

namespace Neptune::WebGPU::Unit {

	Adapter::~Adapter()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

        wgpuAdapterRelease(m_Handle);
	}

	void Adapter::CreateAdapter(WGPUInstance instance)
	{
		NEPTUNE_PROFILE_ZONE

		WGPURequestAdapterOptions options{};

        static auto request = [](
            WGPURequestAdapterStatus status    , 
            WGPUAdapter              adapter   , 
            WGPUStringView           message   , 
            void*                    userdata1 , 
            void*
        ) {
            if (auto p = static_cast<WGPUAdapter*>(userdata1)) 
            {
                *p = adapter;
            }
        };

        WGPURequestAdapterCallbackInfo       info{};
        info.mode                          = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                     = &m_Handle;
        info.callback                      = request;

        auto future = wgpuInstanceRequestAdapter(instance, &options, info);

        WGPUFutureWaitInfo                   waitInfo{};
        waitInfo.future                    = future;

        WEBGPU_WAIT_CHECK(wgpuInstanceWaitAny(instance, 1, &waitInfo, WaitTimeoutNS))
	}

}

#endif