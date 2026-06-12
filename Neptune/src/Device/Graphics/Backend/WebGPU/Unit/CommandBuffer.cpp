/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

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
	
	void CommandBuffer::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuCommandBufferSetLabel(m_Handle, { name.c_str(), name.size() });
	}
}

#endif