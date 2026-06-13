/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Graphics::RHI {
    
    /**
    * @brief Enum of RHI.
    */
    enum class ERHI : uint8_t
    {
        RenderPass = 0,
        DescriptorList,
        Pipeline,
        Shader,
        RenderTarget,
        VertexBuffer,
        IndexBuffer,
        CmdList,
        CmdList2,
        Decoder,
        OpticalFlow,

        Count
    };
    
}