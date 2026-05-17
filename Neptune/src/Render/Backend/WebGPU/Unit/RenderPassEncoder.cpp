/**
* @file RenderPassEncoder.cpp.
* @brief The RenderPassEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

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
	
}

#endif