/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Infrastructure.h"

namespace Neptune::OpenGL {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: ContextAccessor(context)
		, m_EInfrastructure(e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (m_EInfrastructure)
        {
            case EInfrastructure::DebugUtilsObject:                   return "DebugUtilsObject";
            case EInfrastructure::GraphicFence:                       return "GraphicFence";

            default:                                                  return "NonNamed";
        }
    }
}

#endif