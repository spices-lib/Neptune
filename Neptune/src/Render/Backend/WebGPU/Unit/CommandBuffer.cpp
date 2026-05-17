/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "CommandBuffer.h"

namespace Neptune::WebGPU::Unit {

	CommandBuffer::~CommandBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuCommandBufferRelease(m_Handle);
	}

	void CommandBuffer::CreateCommandBuffer(WGPUCommandEncoder encoder, const WGPUCommandBufferDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle = wgpuCommandEncoderFinish(encoder, &desc);
	}
}

#endif