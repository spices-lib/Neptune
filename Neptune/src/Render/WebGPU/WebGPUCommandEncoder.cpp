/**
* @file WebGPUCommandEncoder.cpp.
* @brief The WebGPUCommandEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPUCommandEncoder.h"

namespace Neptune {

    WebGPUCommandEncoder::WebGPUCommandEncoder(WebGPUState& webGPUState)
            : WebGPUObject(webGPUState)
    {
        WGPUCommandEncoderDescriptor desc = {};
        webGPUState.m_GraphicCommandEncoder = wgpuDeviceCreateCommandEncoder(webGPUState.m_Device, &desc);
    }

}