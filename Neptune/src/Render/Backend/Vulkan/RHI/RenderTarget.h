#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Resource/Image.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/Resource/DescriptorSet.h"

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	class RenderTarget : public ContextAccessor, public RHI::RHIRenderTarget::Impl
	{
	public:

		RenderTarget(Context& context) : ContextAccessor(context), m_DescriptorSet(context) {}
		~RenderTarget() = default;

		void SetImage(SP<Image> image) { m_Image = image; }

		void CreateRenderTarget(const RenderTargetCreateInfo& info) override;

		void* CreateBindingID() override;

		bool CopyToRenderTarget(SP<RHI::RenderTarget> target) override;

		TextureFormat GetFormat() const override;

		uint32_t GetWidth() const override { return m_Image->Width(); }

		uint32_t GetHeight() const override { return m_Image->Height(); }

		const VkImage& Handle() const { return m_Image->Handle(); }

		SP<Image> IHandle() { return m_Image; }

		const VkImageView& GetView() const { return m_Image->GetView(); }

		const VkSampler& GetSampler() const { return m_Image->GetSampler(); }

		bool CopyToRenderTarget(SP<RenderTarget> target);

	private:

		void CreateColorRenderTarget(const RenderTargetCreateInfo& info);

		void CreateDepthRenderTarget(const RenderTargetCreateInfo& info);

	private:

		SP<Image> m_Image;
		DescriptorSet m_DescriptorSet;
	};
}