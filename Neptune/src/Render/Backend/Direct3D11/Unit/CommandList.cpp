/**
* @file CommandList.cpp.
* @brief The CommandList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandList.h"

namespace Neptune::Direct3D11::Unit {

	CommandList::~CommandList()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

}

#endif