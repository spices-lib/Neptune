/**
* @file WebGPUAdapter.cpp.
* @brief The WebGPUAdapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUAdapter.h"

namespace Neptune {

	WebGPUAdapter::WebGPUAdapter(WebGPUContext& context)
		: WebGPUObject(context, EWebGPUObject::WebGPUInstance)
	{}

    void WebGPUAdapter::GetFeatures() {}
    void WebGPUAdapter::GetInfo() {}
    void WebGPUAdapter::GetLimits() {}
    void WebGPUAdapter::HasFeature() {}
    void WebGPUAdapter::RequestDevice() {}
    void WebGPUAdapter::AddRef() {}
    void WebGPUAdapter::Release() {}
}

#endif