/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DebugUtilsObject.h"

#ifdef NEPTUNE_DEBUG
#define USE_PIX
#endif

#include <pix3.h>

namespace Neptune::Direct3D12 {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::BeginLabel(D3D12GraphicsCommandList cmdList, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		PIXBeginEvent(cmdList, 0, caption.c_str());
	}

	void DebugUtilsObject::EndLabel(D3D12GraphicsCommandList cmdList) const
	{
		NEPTUNE_PROFILE_ZONE

		PIXEndEvent(cmdList);
	}

	void DebugUtilsObject::InsertLabel(D3D12GraphicsCommandList cmdList, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

		PIXSetMarker(cmdList, 0, caption.c_str());
	}
}

#endif