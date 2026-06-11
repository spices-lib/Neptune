/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "RenderPass.h"

namespace Neptune::OpenGL {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE

	}

	void RenderPass::AddColorAttachment(SP<RHI::RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void RenderPass::Build(uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE


	}
	
}

#endif