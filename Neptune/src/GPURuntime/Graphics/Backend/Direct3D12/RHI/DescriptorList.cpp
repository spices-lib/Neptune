/**
* @file DescriptorList.cpp.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DescriptorList.h"

namespace Neptune::Direct3D12 {

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