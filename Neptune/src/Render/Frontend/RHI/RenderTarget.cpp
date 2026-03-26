#include "Pchheader.h"
#include "RenderTarget.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::RHI {

	void RenderTarget::CreateRenderTarget(const RenderTargetCreateInfo& info)
	{
		RHIRenderTarget::m_Impl->CreateRenderTarget(info);
	}
}