/**
* @file RenderPassEncoder.cpp.
* @brief The RenderPassEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "RenderPassEncoder.h"

namespace Neptune::WebGPU::Unit {

	RenderPassEncoder::~RenderPassEncoder()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuRenderPassEncoderRelease(m_Handle);
	}

	void RenderPassEncoder::Begin(WGPUCommandEncoder encoder,  const WGPURenderPassDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle = wgpuCommandEncoderBeginRenderPass(encoder, &desc);
	}
	
	void RenderPassEncoder::End() const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderEnd(m_Handle);
	}
	
	void RenderPassEncoder::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
    	
		wgpuRenderPassEncoderSetLabel(m_Handle, { name.c_str(), name.size() });
	}
	
}

#endif