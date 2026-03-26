#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Texture/RenderTarget.h"
#include "Render/Frontend/Utils.h"
#include <any>

namespace Neptune::RHI {
	
	using RHIRenderPass = RHI<ERHI::RenderPass>;

	template<>
	class RHIRenderPass::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void AddSwapChainAttachment() = 0;

		virtual void AddColorAttachment(SP<class RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info) = 0;

		virtual void Build(uint32_t count = MaxFrameInFlight) = 0;
	};

	class RenderPass : public RHIRenderPass
	{
	public:

		RenderPass() = default;
		~RenderPass() override = default;
		
		void AddSwapChainAttachment() const { RHIRenderPass::m_Impl->AddSwapChainAttachment(); }

		void AddColorAttachment(SP<class RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info) const { RHIRenderPass::m_Impl->AddColorAttachment(renderTarget, info); }

		void Build(uint32_t count = MaxFrameInFlight) const { RHIRenderPass::m_Impl->Build(count); }

	};
}