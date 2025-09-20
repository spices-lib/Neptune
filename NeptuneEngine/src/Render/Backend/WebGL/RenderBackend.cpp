/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"

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

namespace Neptune::WebGL {

    RenderBackend::RenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        NEPTUNE_PROFILE_ZONE

        EmscriptenWebGLContextAttributes attrs;
        emscripten_webgl_init_context_attributes(&attrs);
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#nepnep", &attrs);
        emscripten_webgl_make_context_current(ctx);
    }

    RenderBackend::~RenderBackend()
    {

    }

    void RenderBackend::BeginFrame()
    {

    }

    void RenderBackend::EndFrame()
    {

    }

    void RenderBackend::RenderFrame()
    {
        NEPTUNE_PROFILE_ZONE

        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

#endif