/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Window Implement.
    */
    enum class WindowImplement : uint8_t
    {
        None = 0,
        GLFW,
        emscripten_glfw,
        SDL2,
        WindowsNative,
        MacOSNative,
        LinuxNative,

        Count
    };

}