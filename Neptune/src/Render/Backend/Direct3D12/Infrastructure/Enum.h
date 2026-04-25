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

        GraphicQueue,                        // @brief Main Thread Graphic Queue.
        ComputeQueue,                        // @brief Main Thread Compute Queue.

        SwapChain,                           // @brief SwapChain.

        GraphicCommandAllocator,             // @brief Main Thread Graphic CommandAllocator.
        GraphicCommandList,                  // @brief Main Thread Graphic CommandList.

        ComputeCommandAllocator,             // @brief Main Thread Compute CommandAllocator.
        ComputeCommandList,                  // @brief Main Thread Compute CommandList.

        GraphicFence,                        // @brief Main Thread Graphic Fence.

        ComputeFence,                        // @brief Main Thread Compute Fence.

        Count
    };

}

#endif