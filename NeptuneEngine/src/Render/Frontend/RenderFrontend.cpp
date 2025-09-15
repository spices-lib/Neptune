/**
* @file RenderFrontEnd.cpp.
* @brief The RenderFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontend.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include "Render/Backend/WebGPU/RenderBackend.h"
#include "Render/Backend/WebGL/RenderBackend.h"
#endif

#ifdef NP_PLATFORM_WINDOWS
#include "Render/Backend/Vulkan/RenderBackend.h"
#include "Render/Backend/OpenGL/RenderBackend.h"
#endif

namespace Neptune {

    SP<RenderFrontend> RenderFrontend::Create(RenderBackendEnum backend)
    {
        switch(backend)
        {
#ifdef NP_PLATFORM_EMSCRIPTEN
            case RenderBackendEnum::WebGPU: return CreateSP<WebGPU::RenderBackend>(backend);
            case RenderBackendEnum::WebGL:  return CreateSP<WebGL::RenderBackend>(backend);
#endif

#ifdef NP_PLATFORM_WINDOWS
            case RenderBackendEnum::Vulkan: return CreateSP<Vulkan::RenderBackend>(backend);
            case RenderBackendEnum::OpenGL: return CreateSP<OpenGL::RenderBackend>(backend);
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