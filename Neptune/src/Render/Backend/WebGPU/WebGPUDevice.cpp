/**
* @file WebGPUDevice.cpp.
* @brief The WebGPUDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUDevice.h"

namespace Neptune {

    static void WebGPUErrorCallback(WGPUErrorType error_type, const char* message, void*)
    {
        const char* error_type_lbl = "";
        switch (error_type)
        {
            case WGPUErrorType_Validation:  error_type_lbl = "Validation"; break;
            case WGPUErrorType_OutOfMemory: error_type_lbl = "Out of memory"; break;
            case WGPUErrorType_Unknown:     error_type_lbl = "Unknown"; break;
            case WGPUErrorType_Internal:    error_type_lbl = "Internal"; break;
            case WGPUErrorType_Force32:     error_type_lbl = "Force32"; break;
            default:                        error_type_lbl = "Unknown";
        }

        std::stringstream ss;
        ss << error_type_lbl << "error: " << message;

        NEPTUNE_CORE_ERROR(ss.str())
    }

    WebGPUDevice::WebGPUDevice(WebGPUState& webGPUState)
            : WebGPUObject(webGPUState)
    {
        CreateDevice();
        CreateSurface();
        QuerySwapChainSupport();
        CreateQueue();
    }

    void WebGPUDevice::CreateDevice()
    {
        m_WebGPUState.m_Device = emscripten_webgpu_get_device();
        if (!m_WebGPUState.m_Device)
        {
            return;
        }
    }

    void WebGPUDevice::CreateSurface()
    {
        WGPUStringView selector{};
        selector.data = "#nepnep";
        selector.length = strlen(selector.data);
        
        WGPUEmscriptenSurfaceSourceCanvasHTMLSelector htmlSelector  = {};
        htmlSelector.chain.sType                                    = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
        htmlSelector.chain.next                                     = nullptr;
        htmlSelector.selector                                       = selector;

        WGPUSurfaceDescriptor surfaceDesc                           = {};
        surfaceDesc.nextInChain                                     = &htmlSelector.chain;

        m_WebGPUState.m_Surface = wgpuInstanceCreateSurface(m_WebGPUState.m_Instance, &surfaceDesc);

        WGPUTextureFormat viewFormats[] = { WGPUTextureFormat_RGBA8Unorm };
        
        WGPUSurfaceConfiguration configure                          = {};
        configure.device                                            = m_WebGPUState.m_Device;
        configure.format                                            = WGPUTextureFormat_RGBA8Unorm;
        configure.usage                                             = WGPUTextureUsage_RenderAttachment;
        configure.width                                             = 1920;
        configure.height                                            = 1080;
        configure.viewFormatCount                                   = 1;
        configure.viewFormats                                       = viewFormats;
        configure.alphaMode                                         = WGPUCompositeAlphaMode_Premultiplied;
        configure.presentMode                                       = WGPUPresentMode_Fifo;
        
        wgpuSurfaceConfigure(m_WebGPUState.m_Surface, &configure);
    }

    void WebGPUDevice::QuerySwapChainSupport()
    {
        WGPUAdapter adapter                                         = {};

        WGPUSurfaceCapabilities capabilities                        = {};
        WEBGPU_CHECK(wgpuSurfaceGetCapabilities(m_WebGPUState.m_Surface, adapter, &capabilities));

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

    void WebGPUDevice::CreateQueue()
    {
        m_WebGPUState.m_GraphicQueue = wgpuDeviceGetQueue(m_WebGPUState.m_Device);
    }

}

#endif