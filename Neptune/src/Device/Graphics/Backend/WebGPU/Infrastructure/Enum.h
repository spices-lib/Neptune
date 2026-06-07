/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

namespace Neptune::WebGPU {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Instance = 0,                        // @brief Instance.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Surface,                             // @brief Surface.
        Adapter,                             // @brief Adapter.
        Device,                              // @brief LogicalDevice.

        Queue,                               // @brief Queue.
        
        Future,                              // @brief Queue Fence.

        CommandEncoder,                      // @brief CommandEncoder.
        
        Count
    };

}

#endif