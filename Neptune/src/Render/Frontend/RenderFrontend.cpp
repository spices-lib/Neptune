/**
* @file RenderFrontEnd.cpp.
* @brief The RenderFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontend.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include "Render/Backend/WebGPU/WebGPURenderBackend.h"
#endif

namespace Neptune {

    SP<RenderFrontend> RenderFrontend::Create(RenderBackendEnum backend)
    {
        switch(backend)
        {
#ifdef NP_PLATFORM_EMSCRIPTEN
            case RenderBackendEnum::WebGPU: return CreateSP<WebGPURenderBackend>(backend);
#endif
            default:
            {
                printf("Not Supported Render Backend.\n");
            }
        }

        return nullptr;
    }

}