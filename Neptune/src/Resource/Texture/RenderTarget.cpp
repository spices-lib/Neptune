#include "Pchheader.h"
#include "RenderTarget.h"
#include "Render/Frontend/RHI/RenderTarget.h"

namespace Neptune {

	RenderTarget::RenderTarget()
	{
		m_RHIResource = CreateSP<RHI::RenderTarget>();

		m_RHIResource->CreateRenderTarget({});
	}

	RenderTarget::RenderTarget(const RenderTargetCreateInfo& info)
	{
		m_RHIResource = CreateSP<RHI::RenderTarget>();

		m_RHIResource->CreateRenderTarget(info);
	}

	bool RenderTarget::CopyToRenderTarget(SP<RenderTarget> target)
	{
		return m_RHIResource->CopyToRenderTarget(target->GetRHIResource().get());
	}
}