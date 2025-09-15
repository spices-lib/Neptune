/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Surface.h"
#include "Instance.h"
#include "Device.h"
#include "Adapter.h"

namespace Neptune::WebGPU {

    Surface::Surface(Context& context)
        : Infrastructure(context)
    {
        m_Handle = m_Context.Get<Instance>()->CreateSurface("#nepnep");

        if (m_Handle)
        {
            NEPTUNE_CORE_INFO("WGPUSurface created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUSurface created failed.")
        }

        Configure();
    }

    void Surface::Configure()
    {
        WGPUTextureFormat viewFormats[] = { WGPUTextureFormat_RGBA8Unorm };
        
        WGPUSurfaceConfiguration configure                          = {};
        configure.device                                            = m_Context.Get<Device>()->Handle();
        configure.format                                            = WGPUTextureFormat_RGBA8Unorm;
        configure.usage                                             = WGPUTextureUsage_RenderAttachment;
        configure.width                                             = 1920;
        configure.height                                            = 1080;
        configure.viewFormatCount                                   = 1;
        configure.viewFormats                                       = viewFormats;
        configure.alphaMode                                         = WGPUCompositeAlphaMode_Premultiplied;
        configure.presentMode                                       = WGPUPresentMode_Fifo;
        
        wgpuSurfaceConfigure(m_Handle, &configure);
    }

    void Surface::GetCapabilities()
    {
        WGPUSurfaceCapabilities capabilities{};

        WEBGPU_CHECK(wgpuSurfaceGetCapabilities(m_Handle, m_Context.Get<Adapter>()->Handle(), &capabilities))
    }

    void Surface::GetCurrentTexture()
    {
        WGPUSurfaceTexture texture{};

        wgpuSurfaceGetCurrentTexture(m_Handle, &texture);
    }

    void Surface::Present()
    {
        WEBGPU_CHECK(wgpuSurfacePresent(m_Handle))
    }

    void Surface::Unconfigure()
    {
        wgpuSurfaceUnconfigure(m_Handle);
    }

}

#endif