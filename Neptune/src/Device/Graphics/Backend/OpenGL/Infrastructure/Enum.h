/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

namespace Neptune::OpenGL {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        WindowContext = 0,                   // @brief Window/Context.
        DebugUtilsObject,                    // @brief Label/Name Functors.

        GraphicFence,                        // @brief Main Thread Graphic Fence.

        Count
    };

}

#endif