/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderPass.h"
#include "Render/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

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