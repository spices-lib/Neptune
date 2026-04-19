/**
* @file DescriptorList.cpp.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DescriptorList.h"
#include "Render/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

namespace Neptune::OpenGL {

	void DescriptorList::AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void DescriptorList::AddUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void DescriptorList::UpdateUniformBuffer(uint32_t set, uint32_t binding, void* data)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void DescriptorList::UpdateUniformTexture(uint32_t set, uint32_t binding, SP<RHI::RenderTarget> renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void DescriptorList::CombineSharedLayout(const RHI::RHIDescriptorList::Impl* shared)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void DescriptorList::Build()
	{
		NEPTUNE_PROFILE_ZONE

	}
	
}

#endif