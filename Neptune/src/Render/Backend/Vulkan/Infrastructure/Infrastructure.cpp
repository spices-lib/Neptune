/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Infrastructure.h"

namespace Neptune::Vulkan {

	Infrastructure::Infrastructure(Context& context)
		: m_Context(context)
	{}

	Infrastructure::~Infrastructure()
	{
		NEPTUNE_PROFILE_ZONE

		Destroy(this);
	}

}

#endif