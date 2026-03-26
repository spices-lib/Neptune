#include "Pchheader.h"
#include "BasePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/DescriptorList.h"
#include "Render/Frontend/RHI/CmdList.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Resource/Shader/Shader.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Shader/Shader.h"
#include "Resource/ResourcePool.h"
#include "Resource/Mesh/Mesh.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"

namespace Neptune::Render {

	void BasePass::OnConstruct()
	{
		{
			auto& resourcePool = ResourcePool<RenderTarget>::Instance();

			RenderTargetCreateInfo    info{};
			info.format             = TextureFormat::RGBA16_SFLOAT;
			info.domain             = TextureDomain::Texture2D;
			info.width              = m_RTSize.x;
			info.height             = m_RTSize.y;

			resourcePool.CreateResource("Scene", info);

			if (!resourcePool.HasResource("CurrDecodeRT"))
			{
				resourcePool.CreateResource("CurrDecodeRT");
			}
		}

		RenderTargetAttachmentInfo                  info{};
		info.loadOp                               = AttachmentOP::Clear;
		info.enableBlend                          = false;
		info.inLayout                             = AttachmentLayout::Undefined;
		info.outLayout                            = AttachmentLayout::ColorAttachment;

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment(ResourcePool<RenderTarget>::Instance().GetResource("Scene")->GetRHIResource(), info);
		m_RenderPass->Build();
		
		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->AddUniformTexture(1, 0, ResourcePool<RenderTarget>::Instance().GetResource("CurrDecodeRT")->GetRHIResource());
		m_DescriptorList->CombineSharedLayout();
		m_DescriptorList->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptorList(m_DescriptorList);
		m_Pipeline->SetCullMode(CullMode::None);
		
		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.HasResource("BasePassVert"))
			{
				auto s = resourcePool.CreateResource("BasePassVert");

				s->SetStage(ShaderStage::Vertex);
				s->SetSource("src/Assets/Shader/BasePass.vert");
			}

            auto shader = resourcePool.GetResource("BasePassVert");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.HasResource("BasePassFrag"))
			{
				auto s = resourcePool.CreateResource("BasePassFrag");

				s->SetStage(ShaderStage::Fragment);
				s->SetSource("src/Assets/Shader/BasePass.frag");
			}

            auto shader = resourcePool.GetResource("BasePassFrag");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		m_Pipeline->BuildGraphicPipeline();
	}

	void BasePass::OnRender(Scene* scene)
	{
		const auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		m_DescriptorList->UpdateUniformTexture(1, 0, ResourcePool<RenderTarget>::Instance().GetResource("CurrDecodeRT")->GetRHIResource());

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdSetViewport(m_RTSize);

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList);

		cmdList.CmdDrawFullScreenTriangle();

		cmdList.CmdEndRenderPass();
	}

}