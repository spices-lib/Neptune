/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

namespace Neptune::Vulkan {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Functions = 0,                       // @brief Functors.
        Instance,                            // @brief Instance.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Surface,                             // @brief Surface.
        PhysicalDevice,                      // @brief PhysicalDevice.
        Device,                              // @brief LogicalDevice.
                                             
        GraphicQueue,                        // @brief Main Thread Graphic Queue.
        PresentQueue,                        // @brief Main Thread Present Queue.
        ComputeQueue,                        // @brief Main Thread Compute Queue.

        GraphicThreadQueue,                  // @brief Sub Thread Graphic Queue.
        ComputeThreadQueue,                  // @brief Sub Thread Compute Queue.
        TransferThreadQueue,                 // @brief Sub Thread Transfer Queue.
        VideoEncodeThreadQueue,              // @brief Sub Thread VideoEncode Queue.
        VideoDecodeThreadQueue,              // @brief Sub Thread VideoDecode Queue.
        OpticalFlowThreadQueue,              // @brief Sub Thread OpticalFlow Queue.
                                             
        MemoryAllocator,                     // @brief VMA.
        SwapChain,                           // @brief SwapChain.
                                             
        GraphicImageSemaphore,               // @brief Main Thread Graphic ImageSemaphore.
        GraphicQueueSemaphore,               // @brief Main Thread Graphic QueueSemaphore.
        GraphicFence,                        // @brief Main Thread Graphic Fence.
                                             
        ComputeQueueSemaphore,               // @brief Main Thread Compute QueueSemaphore.
        ComputeFence,                        // @brief Main Thread Compute Fence.
                                             
        GraphicCommandPool,                  // @brief Main Thread Graphic CommandPool.
        GraphicCommandBuffer,                // @brief Main Thread Graphic CommandBuffer.

        ComputeCommandPool,                  // @brief Main Thread Compute CommandPool.
        ComputeCommandBuffer,                // @brief Main Thread Compute CommandBuffer.

        GraphicThreadCommandPool,            // @brief Sub Thread Graphic CommandPool.
        ComputeThreadCommandPool,            // @brief Sub Thread Compute CommandPool.
        TransferThreadCommandPool,           // @brief Sub Thread Transfer CommandPool.
        VideoEncodeThreadCommandPool,        // @brief Sub Thread VideoEncode CommandPool.
        VideoDecodeThreadCommandPool,        // @brief Sub Thread VideoDecode CommandPool.
        OpticalFlowThreadCommandPool,        // @brief Sub Thread OpticalFlow CommandPool.

        DescriptorPool,                      // @brief DescriptorPool.

        Count
    };

}

#endif