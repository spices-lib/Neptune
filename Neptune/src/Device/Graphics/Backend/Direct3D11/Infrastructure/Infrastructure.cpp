/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Infrastructure.h"

namespace Neptune::Direct3D11 {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
        : Super(context, e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (m_EInfrastructure)
        {
            case EInfrastructure::DebugUtilsObject:                   return "DebugUtilsObject";
            case EInfrastructure::DeviceContext:                      return "DeviceContext";
            case EInfrastructure::Factory:                            return "Factory";
            case EInfrastructure::Device:                             return "Device";
            case EInfrastructure::SwapChain:                          return "SwapChain";
            case EInfrastructure::GraphicFence:                       return "GraphicFence";
            case EInfrastructure::ComputeFence:                       return "ComputeFence";
            case EInfrastructure::GraphicCommandList:                 return "GraphicCommandList";
            case EInfrastructure::ComputeCommandList:                 return "ComputeCommandList";
            case EInfrastructure::GraphicThreadCommandList:           return "GraphicThreadCommandList";
            case EInfrastructure::ComputeThreadCommandList:           return "ComputeThreadCommandList";
            default:                                                  return "NonNamed";
        }
    }
}

#endif