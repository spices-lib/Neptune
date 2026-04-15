/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Infrastructure.h"
#include "Instance.h"

namespace Neptune::Vulkan {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: ContextAccessor(context)
		, m_EInfrastructure(e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (m_EInfrastructure)
        {
            case EInfrastructure::Instance:                           return "Instance";
            case EInfrastructure::Functions:                          return "Functions";
            case EInfrastructure::DebugUtilsObject:                   return "DebugUtilsObject";
            case EInfrastructure::Surface:                            return "Surface";
            case EInfrastructure::PhysicalDevice:                     return "PhysicalDevice";
            case EInfrastructure::Device:                             return "Device";
                                                                      
            case EInfrastructure::GraphicQueue:                       return "GraphicQueue";
            case EInfrastructure::PresentQueue:                       return "PresentQueue";
            case EInfrastructure::ComputeQueue:                       return "ComputeQueue";
                                                                      
            case EInfrastructure::GraphicThreadQueue:                 return "GraphicThreadQueue";
            case EInfrastructure::ComputeThreadQueue:                 return "ComputeThreadQueue";
            case EInfrastructure::TransferThreadQueue:                return "TransferThreadQueue";
            case EInfrastructure::VideoEncodeThreadQueue:             return "VideoEncodeThreadQueue";
            case EInfrastructure::VideoDecodeThreadQueue:             return "VideoDecodeThreadQueue";
            case EInfrastructure::OpticalFlowThreadQueue:             return "OpticalFlowThreadQueue";
                                                                      
            case EInfrastructure::MemoryAllocator:                    return "MemoryAllocator";
            case EInfrastructure::SwapChain:                          return "SwapChain";
                                                                      
            case EInfrastructure::GraphicImageSemaphore:              return "GraphicImageSemaphore";
            case EInfrastructure::GraphicQueueSemaphore:              return "GraphicQueueSemaphore";
            case EInfrastructure::GraphicFence:                       return "GraphicFence";
                                                                      
            case EInfrastructure::ComputeQueueSemaphore:              return "ComputeQueueSemaphore";
            case EInfrastructure::ComputeFence:                       return "ComputeFence";
                                                                      
            case EInfrastructure::GraphicCommandPool:                 return "GraphicCommandPool";
            case EInfrastructure::GraphicCommandBuffer:               return "GraphicCommandBuffer";
                                                                      
            case EInfrastructure::ComputeCommandPool:                 return "ComputeCommandPool";
            case EInfrastructure::ComputeCommandBuffer:               return "ComputeCommandBuffer";
                                                                      
            case EInfrastructure::GraphicThreadCommandPool:           return "GraphicThreadCommandPool";
            case EInfrastructure::ComputeThreadCommandPool:           return "ComputeThreadCommandPool";
            case EInfrastructure::TransferThreadCommandPool:          return "TransferThreadCommandPool";
            case EInfrastructure::VideoEncodeThreadCommandPool:       return "VideoEncodeThreadCommandPool";
            case EInfrastructure::VideoDecodeThreadCommandPool:       return "VideoDecodeThreadCommandPool";
            case EInfrastructure::OpticalFlowThreadCommandPool:       return "OpticalFlowThreadCommandPool";

            case EInfrastructure::DescriptorPool:                     return "DescriptorPool";

            default:                                                  return "NonNamed";
        }
    }
}

#endif