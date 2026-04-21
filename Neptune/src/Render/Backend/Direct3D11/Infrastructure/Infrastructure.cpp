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
		: ContextAccessor(context)
		, m_EInfrastructure(e)
	{}

	std::string Infrastructure::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (m_EInfrastructure)
        {
            default:                                                  return "NonNamed";
        }
    }
}

#endif