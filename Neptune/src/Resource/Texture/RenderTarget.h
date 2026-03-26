#pragma once
#include "Core/Core.h"
#include "Texture.h"

namespace Neptune {

	namespace RHI {
	
		class RenderTarget;
	}

	enum class RHIMemoryUsage
	{
		Device = 0,
		Host,
		Shared,
		Preserved,
	};

	struct RenderTargetCreateInfo
	{
		uint32_t          width        = 100;
		uint32_t          height       = 100;
		TextureDomain     domain       = TextureDomain::Texture2D;
		TextureFormat     format       = TextureFormat::RGBA8_UNORM;
		RHIMemoryUsage    memoryUsage  = RHIMemoryUsage::Device;
	};

	enum class AttachmentOP : uint8_t
	{
		Clear = 0,
		Load,

		Count
	};

	enum class AttachmentLayout : uint8_t
	{
		Undefined = 0,
		ColorAttachment,
		ShaderRead,

		Count
	};

	struct RenderTargetAttachmentInfo
	{
		bool               enableBlend = false;
		AttachmentOP       loadOp = AttachmentOP::Clear;
		AttachmentLayout   inLayout = AttachmentLayout::Undefined;
		AttachmentLayout   outLayout = AttachmentLayout::ColorAttachment;
	};

	class RenderTarget
	{
	public:

		RenderTarget();

		RenderTarget(const RenderTargetCreateInfo& info);

		virtual ~RenderTarget() = default;

		SP<RHI::RenderTarget> GetRHIResource() { return m_RHIResource; }

		void SetName(const std::string& name) { m_Name = name; }

		bool CopyToRenderTarget(SP<RenderTarget> target);

	private:

		std::string           m_Name;
		SP<RHI::RenderTarget> m_RHIResource;
	};
}