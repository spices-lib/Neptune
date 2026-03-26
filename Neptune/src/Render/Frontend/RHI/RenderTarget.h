#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Texture/Texture.h"

namespace Neptune {

	struct RenderTargetCreateInfo;
}

namespace Neptune::RHI {
	
	using RHIRenderTarget = RHI<ERHI::RenderTarget>;

	template<>
	class RHIRenderTarget::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void CreateRenderTarget(const RenderTargetCreateInfo& info) = 0;

		virtual void* CreateBindingID() = 0;

		virtual bool CopyToRenderTarget(SP<class RenderTarget> target) = 0;

		virtual TextureFormat GetFormat() const = 0;

		virtual uint32_t GetWidth() const = 0;

		virtual uint32_t GetHeight() const = 0;
	};

	class RenderTarget : public RHIRenderTarget
	{
	public:

		RenderTarget() = default;
		~RenderTarget() override = default;

		void CreateRenderTarget(const RenderTargetCreateInfo& info);

		void* CreateBindingID() { return RHIRenderTarget::m_Impl->CreateBindingID(); }

		bool CopyToRenderTarget(SP<RenderTarget> target) { return RHIRenderTarget::m_Impl->CopyToRenderTarget(target); }

		TextureFormat GetFormat() const { return m_Impl->GetFormat(); }

		uint32_t GetWidth() const { return m_Impl->GetWidth(); }

		uint32_t GetHeight() const { return m_Impl->GetHeight(); }

	};
}