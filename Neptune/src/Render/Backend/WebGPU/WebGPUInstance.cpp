/**
* @file WebGPUInstance.cpp.
* @brief The WebGPUInstance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUInstance.h"

namespace Neptune {

    WebGPUInstance::WebGPUInstance(WebGPUState& webGPUState)
            : WebGPUObject(webGPUState)
    {
        WGPUInstanceDescriptor descriptor{};

        webGPUState.m_Instance = wgpuCreateInstance(&descriptor);
    }

}

#endif