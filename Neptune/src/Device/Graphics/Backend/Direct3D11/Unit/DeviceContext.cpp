/**
* @file DeviceContext.cpp.
* @brief The DeviceContext Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DeviceContext.h"

namespace Neptune::Direct3D11::Unit {

	DeviceContext::~DeviceContext()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

}

#endif