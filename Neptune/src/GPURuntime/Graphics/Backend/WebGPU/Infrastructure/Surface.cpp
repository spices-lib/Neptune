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
#include "DebugUtilsObject.h"

namespace Neptune::WebGPU {

    Surface::Surface(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();

        Configure();
    }

    void Surface::Create()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUEmscriptenSurfaceSourceCanvasHTMLSelector                 htmlSelector{};
        htmlSelector.chain.sType                                    = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
        htmlSelector.chain.next                                     = nullptr;
        htmlSelector.selector                                       = { HTMLCanvas.data(), HTMLCanvas.length() };

        WGPUSurfaceDescriptor                                         desc{};
        desc.nextInChain                                            = &htmlSelector.chain;

        m_Surface.CreateSurface(GetContext().Get<IInstance>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(m_Surface, ToString())
    }

    void Surface::Configure() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUTextureFormat viewFormats[] = { WGPUTextureFormat_RGBA8Unorm };
        
        WGPUSurfaceConfiguration configure                          = {};
        configure.device                                            = GetContext().Get<IDevice>()->Handle();
        configure.format                                            = WGPUTextureFormat_RGBA8Unorm;
        configure.usage                                             = WGPUTextureUsage_RenderAttachment;
        configure.width                                             = 1920;
        configure.height                                            = 1080;
        configure.viewFormatCount                                   = 1;
        configure.viewFormats                                       = viewFormats;
        configure.alphaMode                                         = WGPUCompositeAlphaMode_Premultiplied;
        configure.presentMode                                       = WGPUPresentMode_Fifo;
        
        wgpuSurfaceConfigure(m_Surface.GetHandle(), &configure);
    }

    void Surface::GetCapabilities() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSurfaceCapabilities capabilities{};

        WEBGPU_CHECK(wgpuSurfaceGetCapabilities(m_Surface.GetHandle(), GetContext().Get<IAdapter>()->Handle(), &capabilities))
    }

    void Surface::GetCurrentTexture() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUSurfaceTexture texture{};

        wgpuSurfaceGetCurrentTexture(m_Surface.GetHandle(), &texture);
    }

    void Surface::Present() const
    {
        NEPTUNE_PROFILE_ZONE

        WEBGPU_CHECK(wgpuSurfacePresent(m_Surface.GetHandle()))
    }

    void Surface::Unconfigure() const
    {
        NEPTUNE_PROFILE_ZONE

        wgpuSurfaceUnconfigure(m_Surface.GetHandle());
    }

}

#endif