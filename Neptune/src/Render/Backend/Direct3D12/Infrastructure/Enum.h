/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

namespace Neptune::Direct3D12 {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Factory,                             // @brief DXGI Factory.
        Device,                              // @brief LogicalDevice.

        Count
    };

}

#endif