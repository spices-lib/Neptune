/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGL

#include "Infrastructure.h"

namespace Neptune::WebGL {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: Super(context, e)
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