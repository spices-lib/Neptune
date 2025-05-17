/**
* @file RenderFrontEnd.cpp.
* @brief The RenderFrontEnd Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontEnd.h"
#include "Render/WebGPU/WebGPURenderBackend.h"

namespace Neptune {

    SP<RenderFrontEnd> RenderFrontEnd::Create(RenderBackendEnum backend)
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