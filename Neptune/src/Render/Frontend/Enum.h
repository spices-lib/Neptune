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
    enum class RenderBackendEnum
    {
        None = 0,
        WebGL = 1,
        WebGPU = 2,
        OpenGL = 3,
        Direct3D11 = 4,
        Direct3D12 = 5,
        Vulkan = 6,
        Metal = 7
    };

}