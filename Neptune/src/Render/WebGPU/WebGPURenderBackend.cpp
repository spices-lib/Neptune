/**
* @file WebGPURenderBackend.cpp.
* @brief The WebGPURenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPURenderBackend.h"
#include "WebGPUInstance.h"
#include "WebGPUDevice.h"
#include "WebGPUCommandEncoder.h"
#include "WebGPUSwapChain.h"

namespace Neptune {

    WebGPURenderBackend::WebGPURenderBackend(RenderBackendEnum backend)
        : RenderFrontEnd(backend)
    {
        m_State     = CreateSP<WebGPUState>();
        m_Instance  = CreateSP<WebGPUInstance>(*m_State);
        m_Device    = CreateSP<WebGPUDevice>(*m_State);

        m_CommandEncoder = CreateSP<WebGPUCommandEncoder>(*m_State);
        m_SwapChain = CreateSP<WebGPUSwapChain>(*m_State, m_Device);
    }

    WebGPURenderBackend::~WebGPURenderBackend()
    {

    }

    void WebGPURenderBackend::BeginFrame()
    {

    }

    void WebGPURenderBackend::EndFrame()
    {
        WGPUCommandBufferDescriptor desc     = {};
        WGPUCommandBuffer commandBuffer      = wgpuCommandEncoderFinish(m_State->m_GraphicCommandEncoder, &desc);

        wgpuQueueSubmit(m_State->m_GraphicQueue, 1, &commandBuffer);
    }

    void WebGPURenderBackend::RenderFrame()
    {

    }
}
