/**
* @file OpenGLRenderBackend.cpp.
* @brief The OpenGLRenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "OpenGLRenderBackend.h"
#include "glad/glad.h"

namespace Neptune {

    OpenGLRenderBackend::OpenGLRenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
    }

    OpenGLRenderBackend::~OpenGLRenderBackend()
    {

    }

    void OpenGLRenderBackend::BeginFrame()
    {

    }

    void OpenGLRenderBackend::EndFrame()
    {

    }

    void OpenGLRenderBackend::RenderFrame()
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

#endif