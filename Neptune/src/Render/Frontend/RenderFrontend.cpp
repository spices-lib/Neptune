/**
* @file RenderFrontEnd.cpp.
* @brief The RenderFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontend.h"
#include "Render/Backend/WebGPU/WebGPURenderBackend.h"

namespace Neptune {

    SP<RenderFrontend> RenderFrontend::Create(RenderBackendEnum backend)
    {
        switch(backend)
        {
            case RenderBackendEnum::WebGPU: return CreateSP<WebGPURenderBackend>(backend);
            default:
            {
                printf("Not Supported Render Backend.\n");
            }
        }

        return nullptr;
    }

}