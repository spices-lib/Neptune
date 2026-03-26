/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderBackend.h"

#include <glad/glad.h>

namespace Neptune::OpenGL {

    RenderBackend::RenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
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

}

#endif