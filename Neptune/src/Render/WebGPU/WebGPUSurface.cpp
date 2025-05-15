/**
* @file WebGPUDevice.cpp.
* @brief The WebGPUDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPUSurface.h"

namespace Neptune {

    WebGPUSurface::WebGPUSurface(
            WebGPUState&       webGPUState ,
            const std::string& name        ,
            const std::string& engineName
    )
            : WebGPUObject(webGPUState)
    {

#ifdef __EMSCRIPTEN__

        WGPUSurfaceDescriptorFromCanvasHTMLSelector html_surface_desc = {};
        html_surface_desc.chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
        html_surface_desc.chain.next = nullptr;
        html_surface_desc.selector = "#canvas";

        WGPUSurfaceDescriptor surface_desc = {};
        surface_desc.nextInChain = &html_surface_desc.chain;

        webGPUState.m_Surface = wgpuInstanceCreateSurface(webGPUState.m_Instance, &surface_desc);

        WGPUAdapter adapter = {};
        WGPUTextureFormat wgpu_preferred_fmt = (WGPUTextureFormat)wgpuSurfaceGetPreferredFormat(webGPUState.m_Surface, adapter);

#else

        wgpu::Surface surface = wgpu::glfw::CreateSurfaceForWindow(instance, window);
        if (!surface)
            return false;
        WGPUTextureFormat wgpu_preferred_fmt = WGPUTextureFormat_BGRA8Unorm;

#endif

    }





}