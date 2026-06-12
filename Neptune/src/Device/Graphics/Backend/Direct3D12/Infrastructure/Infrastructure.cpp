/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Infrastructure.h"

namespace Neptune::Direct3D12 {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
        : Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (m_EInfrastructure)
        {
            case EInfrastructure::DebugUtilsObject:                   return "DebugUtilsObject";
            case EInfrastructure::Factory:                            return "Factory";
            case EInfrastructure::Device:                             return "Device";
            case EInfrastructure::GraphicQueue:                       return "GraphicQueue";
            case EInfrastructure::ComputeQueue:                       return "ComputeQueue";
            case EInfrastructure::SwapChain:                          return "SwapChain";
            case EInfrastructure::GraphicFence:                       return "GraphicFence";
            case EInfrastructure::ComputeFence:                       return "ComputeFence";
            case EInfrastructure::GraphicCommandList:                 return "GraphicCommandList";
            case EInfrastructure::ComputeCommandList:                 return "ComputeCommandList";
            case EInfrastructure::RTVDescriptorHeap:                  return "RTVDescriptorHeap";
            case EInfrastructure::DSVDescriptorHeap:                  return "DSVDescriptorHeap";
            case EInfrastructure::SRVDescriptorHeap:                  return "SRVDescriptorHeap";
            case EInfrastructure::UAVDescriptorHeap:                  return "UAVDescriptorHeap";

            default:                                                  return "NonNamed";
        }
    }
}

#endif