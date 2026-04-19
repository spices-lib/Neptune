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
        WebGL = 0,            // @brief Web
        WebGPU,               // @brief Web
        OpenGL,               // @brief Any
        OpenGLES,             // @brief Mobile
        OpenGLSC,             // @brief Safety Critical
        Direct2D,             // @brief Windows 2D
        Direct3D11,           // @brief Windows
        Direct3D12,           // @brief Windows
        Vulkan,               // @brief Any
        VulkanSC,             // @brief Safety Critical
        Metal,                // @brief Ios Macos Ipados
        GNM,                  // @brief PlayStation
        GNMX,                 // @brief PlayStation
        GDKX,                 // @brief Xbox
        NVN,                  // @brief Nintendo Switch

        Count
    };

}