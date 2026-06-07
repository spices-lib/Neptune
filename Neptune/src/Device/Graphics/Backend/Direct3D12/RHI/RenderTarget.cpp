/**
* @file RenderTarget.cpp.
* @brief The RenderTarget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderTarget.h"

namespace Neptune::Direct3D12 {

	void RenderTarget::CreateRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE
	}

	void* RenderTarget::CreateBindingID()
	{
		NEPTUNE_PROFILE_ZONE

		return nullptr;
	}

	bool RenderTarget::CopyToRenderTarget(const RHI::RenderTarget* target)
	{
		NEPTUNE_PROFILE_ZONE

		return false;
	}

	TextureFormat RenderTarget::GetFormat() const
	{
		NEPTUNE_PROFILE_ZONE

		return TextureFormat::RGBA8_UNORM;
	}

}

#endif