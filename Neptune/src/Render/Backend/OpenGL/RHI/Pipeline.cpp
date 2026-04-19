/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Pipeline.h"
#include "Render/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

namespace Neptune::OpenGL {

	void Pipeline::SetDefault()
	{
		NEPTUNE_PROFILE_ZONE

	}

	void Pipeline::SetRenderPass(SP<RHI::RenderPass> renderPass)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void Pipeline::SetVertexAttributeLayout()
	{

	}

	void Pipeline::SetDescriptorList(SP<RHI::DescriptorList> descriptorList)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void Pipeline::SetCullMode(CullMode mode)
	{
		NEPTUNE_PROFILE_ZONE
	}

	void Pipeline::AddShader(ShaderStage stage, SP<RHI::Shader> shader)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void Pipeline::BuildGraphicPipeline()
	{
		NEPTUNE_PROFILE_ZONE

	}
	
}

#endif