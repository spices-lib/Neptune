/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

namespace Neptune::Direct3D11 {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        DebugUtilsObject,                    // @brief Label/Name Functors.
        DeviceContext,                       // @brief Device Immediate Context.
        Factory,                             // @brief DXGI Factory.
        Device,                              // @brief LogicalDevice.
        
        SwapChain,                           // @brief SwapChain.

        GraphicFence,                        // @brief Main Thread Graphic Fence.
        ComputeFence,                        // @brief Main Thread Compute Fence.

        GraphicCommandList,                  // @brief Main Thread Graphic CommandList.
        ComputeCommandList,                  // @brief Main Thread Compute CommandList.

        GraphicThreadCommandList,            // @brief Sub Thread Graphic CommandList.
        ComputeThreadCommandList,            // @brief Sub Thread Compute CommandList.

        Count
    };

}

#endif