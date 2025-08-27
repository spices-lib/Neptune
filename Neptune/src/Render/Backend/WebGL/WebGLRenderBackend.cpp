/**
* @file WebGLRenderBackend.cpp.
* @brief The WebGLRenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGLRenderBackend.h"

#include <emscripten.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>

#include <GLFW/glfw3.h>
#include <GLFW/emscripten_glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_wgpu.h>

#include <webgpu/webgpu.h>
#include <webgpu/webgpu_cpp.h>
#include "Window/Window.h"

namespace Neptune {

    WebGLRenderBackend::WebGLRenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        EmscriptenWebGLContextAttributes attrs;
        emscripten_webgl_init_context_attributes(&attrs);
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#Nepnep", &attrs);
        emscripten_webgl_make_context_current(ctx);
    }

    WebGLRenderBackend::~WebGLRenderBackend()
    {

    }

    void WebGLRenderBackend::BeginFrame()
    {

    }

    void WebGLRenderBackend::EndFrame()
    {

    }

    void WebGLRenderBackend::RenderFrame()
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

#endif