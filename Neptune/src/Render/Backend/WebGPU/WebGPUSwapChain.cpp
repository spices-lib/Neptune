/**
* @file WebGPUWindows.cpp.
* @brief The WebGPUWindows Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPUSwapChain.h"
#include "WebGPUDevice.h"

namespace Neptune {

    WebGPUSwapChain::WebGPUSwapChain(
            WebGPUState&     webGPUState ,
            SP<WebGPUDevice> webGPUDevice
    )
            : WebGPUObject(webGPUState)
    {
        WGPUSwapChainDescriptor          swapChainDesc = {};
        swapChainDesc.usage            = WGPUTextureUsage_RenderAttachment;
        swapChainDesc.format           = webGPUDevice->GetSwapChainSupport().format;
        swapChainDesc.width            = 1920;
        swapChainDesc.height           = 1080;
        swapChainDesc.presentMode      = webGPUDevice->GetSwapChainSupport().presentMode;

        webGPUState.m_SwapChain = wgpuDeviceCreateSwapChain(webGPUState.m_Device, webGPUState.m_Surface, &swapChainDesc);
    }

    WebGPUSwapChain::~WebGPUSwapChain()
    {
        if (m_WebGPUState.m_SwapChain) {
            wgpuSwapChainRelease(m_WebGPUState.m_SwapChain);
        }
    }



}