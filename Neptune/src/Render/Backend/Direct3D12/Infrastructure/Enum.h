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

        GraphicCommandList,                  // @brief Main Thread Graphic CommandList.
        ComputeCommandList,                  // @brief Main Thread Compute CommandList.

        GraphicFence,                        // @brief Main Thread Graphic Fence.
        ComputeFence,                        // @brief Main Thread Compute Fence.

        RTVDescriptorHeap,                   // @brief Render Target View DescriptorHeap.
        DSVDescriptorHeap,                   // @brief Depth Stencil View DescriptorHeap.
        SRVDescriptorHeap,                   // @brief Shader Resource View DescriptorHeap.
        UAVDescriptorHeap,                   // @brief Unordered Access View DescriptorHeap.

        Count
    };

}

#endif