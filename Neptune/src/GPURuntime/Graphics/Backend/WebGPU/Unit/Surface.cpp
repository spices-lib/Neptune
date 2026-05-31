/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Surface.h"

namespace Neptune::WebGPU::Unit {

	Surface::~Surface()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuSurfaceRelease(m_Handle);
	}

	void Surface::CreateSurface(WGPUInstance instance, const WGPUSurfaceDescriptor& descriptor)
	{
		NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuInstanceCreateSurface(instance, &descriptor);
	}
	
	void Surface::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
    	
		wgpuSurfaceSetLabel(m_Handle, { name.c_str(), name.size() });
	}
	
}

#endif