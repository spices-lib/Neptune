/**
* @file CommandEncoder.cpp.
* @brief The CommandEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "CommandEncoder.h"

namespace Neptune::WebGPU::Unit {

	CommandEncoder::~CommandEncoder()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuCommandEncoderRelease(m_Handle);
	}

	void CommandEncoder::CreateCommandEncoder(WGPUDevice device,  const WGPUCommandEncoderDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle = wgpuDeviceCreateCommandEncoder(device, &desc);
	}
}

#endif