/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

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
            case EInfrastructure::Device:                             return "Device";
            case EInfrastructure::Factory:                            return "Factory";

            default:                                                  return "NonNamed";
        }
    }
}

#endif