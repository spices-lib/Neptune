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
        if(!webGPUState.m_GraphicCommandEncoder)
        {
            WGPUCommandEncoderDescriptor desc = {};
            webGPUState.m_GraphicCommandEncoder = wgpuDeviceCreateCommandEncoder(webGPUState.m_Device, &desc);
        }
    }

    WebGPUCommandEncoder::~WebGPUCommandEncoder()
    {
        if(m_WebGPUState.m_GraphicCommandEncoder)
        {
            wgpuCommandEncoderRelease(m_WebGPUState.m_GraphicCommandEncoder);
            m_WebGPUState.m_GraphicCommandEncoder = nullptr;
        }
    }
}