/**
* @file Factory.cpp.
* @brief The Factory Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Factory.h"

namespace Neptune::Direct3D12::Unit {

	Factory::~Factory()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Factory::CreateFactory(UINT flags)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(CreateDXGIFactory2(flags, IID_PPV_ARGS(&m_Handle)))
	}
}

#endif