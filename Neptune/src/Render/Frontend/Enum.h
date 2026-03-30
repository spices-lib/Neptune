/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Render Backend.
    */
    enum class RenderBackendEnum : uint8_t
    {
        None = 0,
        WebGL,
        WebGPU,
        OpenGL,
        Direct3D11,
        Direct3D12,
        Vulkan,
        Metal,

        Count
    };

}