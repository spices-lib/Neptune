/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Pipeline.h"

namespace Neptune::Direct3D12 {

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