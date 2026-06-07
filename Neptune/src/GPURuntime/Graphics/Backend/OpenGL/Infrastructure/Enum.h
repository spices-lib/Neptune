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
        PresentWindowContext = 0,            // @brief Present Window/Context.
        WindowContext,                       // @brief Window/Context.
        DebugUtilsObject,                    // @brief Label/Name Functors.

        GraphicFence,                        // @brief Main Thread Graphic Fence.

        Count
    };

}

#endif