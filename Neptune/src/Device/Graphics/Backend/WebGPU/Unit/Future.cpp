/**
* @file Future.cpp.
* @brief The Future Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Future.h"

namespace Neptune::WebGPU::Unit {

	void Future::Wait(WGPUInstance instance) const
	{
		NEPTUNE_PROFILE_ZONE

		WGPUFutureWaitInfo                   waitInfo{};
		waitInfo.future                    = m_Handle;

		WEBGPU_WAIT_CHECK(wgpuInstanceWaitAny(instance, 1, &waitInfo, WaitTimeoutNS))
	}
}

#endif