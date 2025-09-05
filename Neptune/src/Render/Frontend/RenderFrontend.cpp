/**
* @file RenderFrontEnd.cpp.
* @brief The RenderFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontend.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include "Render/Backend/WebGPU/WebGPURenderBackend.h"
#include "Render/Backend/WebGL/WebGLRenderBackend.h"
#endif

namespace Neptune {

    SP<RenderFrontend> RenderFrontend::Create(RenderBackendEnum backend)
    {
        switch(backend)
        {
#ifdef NP_PLATFORM_EMSCRIPTEN
            case RenderBackendEnum::WebGPU: return CreateSP<WebGPURenderBackend>(backend);
            case RenderBackendEnum::WebGL:  return CreateSP<WebGLRenderBackend>(backend);
#endif
            default:
            {
                NEPTUNE_CORE_CRITICAL("Not Supported Render Backend.")
                break;
            }
        }

        return nullptr;
    }

}