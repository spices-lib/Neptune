/**
* @file WebGPUDevice.cpp.
* @brief The WebGPUDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPUDevice.h"

#include <emscripten/html5_webgpu.h>

namespace Neptune {

    WebGPUDevice::WebGPUDevice(WebGPUState& webGPUState)
            : WebGPUObject(webGPUState)
    {
        CreateSurface();
        CreateDevice();
    }

    void WebGPUDevice::CreateDevice()
    {

#ifdef __EMSCRIPTEN__

        m_WebGPUState.m_Device = emscripten_webgpu_get_device();
        if (!m_WebGPUState.m_Device)
        {
            return;
        }

#else

        WGPUAdapter adapter = RequestAdapter(m_WebGPUState.m_Instance);
        if (!adapter)
            return false;
        m_WebGPUState.m_Device = RequestDevice(adapter);

#endif

    }

    void WebGPUDevice::CreateSurface()
    {

#ifdef __EMSCRIPTEN__

        WGPUSurfaceDescriptorFromCanvasHTMLSelector htmlSelector    = {};
        htmlSelector.chain.sType                                    = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
        htmlSelector.chain.next                                     = nullptr;
        htmlSelector.selector                                       = "#Nepnep";

        WGPUSurfaceDescriptor surfaceDesc                           = {};
        surfaceDesc.nextInChain                                     = &htmlSelector.chain;

        m_WebGPUState.m_Surface = wgpuInstanceCreateSurface(m_WebGPUState.m_Instance, &surfaceDesc);

#else

        wgpu::Surface surface = wgpu::glfw::CreateSurfaceForWindow(instance, window);
        if (!surface)
            return false;
        WGPUTextureFormat wgpu_preferred_fmt = WGPUTextureFormat_BGRA8Unorm;

#endif

    }

    void WebGPUDevice::QuerySwapChainSupport()
    {
        WGPUAdapter adapter                                         = {};
        WGPUTextureFormat swapChianFormat = (WGPUTextureFormat)wgpuSurfaceGetPreferredFormat(m_WebGPUState.m_Surface, adapter);

        WGPUSurfaceCapabilities capabilities                        = {};
        wgpuSurfaceGetCapabilities(m_WebGPUState.m_Surface, adapter, &capabilities);

        if(capabilities.formatCount != 0) {
            m_SwapChainSupportDetails.format = capabilities.formats[0];

            for(int i = 0; i < capabilities.formatCount; i++) {
                auto format = capabilities.formats[i];
                if(format == WGPUTextureFormat_RGBA8Unorm) {
                    m_SwapChainSupportDetails.format = format;
                    break;
                }
            }
        }

        if(capabilities.presentModeCount != 0) {
            m_SwapChainSupportDetails.presentMode = capabilities.presentModes[0];

            for(int i = 0; i < capabilities.presentModeCount; i++) {
                auto mode = capabilities.presentModes[i];
                if(mode == WGPUPresentMode_Mailbox) {
                    m_SwapChainSupportDetails.presentMode = mode;
                    break;
                }
            }
        }
    }

}