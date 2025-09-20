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
    enum class WindowImplement
    {
        None = 0,
        GLFW = 1,
        emscripten_glfw = 2,
        SDL2 = 3,
        WindowsNative = 4,
        MacOSNative = 5,
        LinuxNative = 6
    };

}