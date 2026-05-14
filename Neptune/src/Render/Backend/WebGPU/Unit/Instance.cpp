/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Instance.h"

namespace Neptune::WebGPU::Unit {

	Instance::~Instance()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuInstanceRelease(m_Handle);
	}

	void Instance::CreateInstance(const WGPUInstanceDescriptor& descriptor)
	{
		NEPTUNE_PROFILE_ZONE

		assert(!m_Handle);

		m_Handle = wgpuCreateInstance(&descriptor);

		if (!m_Handle)
        {
            NEPTUNE_CORE_INFO("WGPUInstance created failed.")
        }
	}
}

#endif