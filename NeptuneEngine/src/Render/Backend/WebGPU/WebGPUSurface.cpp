/**
* @file WebGPUSurface.cpp.
* @brief The WebGPUSurface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUSurface.h"
#include "WebGPUInstance.h"
#include "WebGPUDevice.h"
#include "WebGPUAdapter.h"

namespace Neptune {

    WebGPUSurface::WebGPUSurface(WebGPUContext& context)
        : WebGPUObject(context)
    {
        m_Surface = m_Context.Get<WebGPUInstance>()->CreateSurface("#nepnep");

        if (m_Surface)
        {
            NEPTUNE_CORE_INFO("WGPUSurface created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUSurface created failed.")
        }

        Configure();
    }

    void WebGPUSurface::Configure()
    {
        WGPUTextureFormat viewFormats[] = { WGPUTextureFormat_RGBA8Unorm };
        
        WGPUSurfaceConfiguration configure                          = {};
        configure.device                                            = m_Context.Get<WebGPUDevice>()->Row();
        configure.format                                            = WGPUTextureFormat_RGBA8Unorm;
        configure.usage                                             = WGPUTextureUsage_RenderAttachment;
        configure.width                                             = 1920;
        configure.height                                            = 1080;
        configure.viewFormatCount                                   = 1;
        configure.viewFormats                                       = viewFormats;
        configure.alphaMode                                         = WGPUCompositeAlphaMode_Premultiplied;
        configure.presentMode                                       = WGPUPresentMode_Mailbox;
        
        wgpuSurfaceConfigure(m_Surface, &configure);
    }

    void WebGPUSurface::GetCapabilities()
    {
        WGPUSurfaceCapabilities capabilities{};

        WEBGPU_CHECK(wgpuSurfaceGetCapabilities(m_Surface, m_Context.Get<WebGPUAdapter>()->Row(), &capabilities))
    }

    void WebGPUSurface::GetCurrentTexture()
    {
        WGPUSurfaceTexture texture{};

        wgpuSurfaceGetCurrentTexture(m_Surface, &texture);
    }

    void WebGPUSurface::Present()
    {
        WEBGPU_CHECK(wgpuSurfacePresent(m_Surface))
    }

    void WebGPUSurface::Unconfigure()
    {
        wgpuSurfaceUnconfigure(m_Surface);
    }

}

#endif