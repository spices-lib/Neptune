/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

namespace Neptune::OpenGL {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        DebugUtilsObject = 0,                // @brief Label/Name Functors.

        GraphicFence,                        // @brief Main Thread Graphic Fence.

        Count
    };

}

#endif