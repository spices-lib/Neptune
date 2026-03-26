#include "Pchheader.h"
#include "FPSPass.h"
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

	void FPSPass::OnConstruct()
	{
		RenderTargetAttachmentInfo   info{};
		info.loadOp                = AttachmentOP::Load;
		info.enableBlend           = true;
		info.inLayout              = AttachmentLayout::ColorAttachment;
		info.outLayout             = AttachmentLayout::ShaderRead;

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment(ResourcePool<RenderTarget>::Instance().GetResource("Scene")->GetRHIResource(), info);
		m_RenderPass->Build();
		
		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->CombineSharedLayout();
		m_DescriptorList->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptorList(m_DescriptorList);
		m_Pipeline->SetCullMode(CullMode::None);
		
		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.HasResource("FPSPassVert"))
			{
				auto s = resourcePool.CreateResource("FPSPassVert");

				s->SetStage(ShaderStage::Vertex);
				s->SetSource("src/Assets/Shader/FPSPass.vert");
			}

            auto shader = resourcePool.GetResource("FPSPassVert");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		{
			auto& resourcePool = ResourcePool<Shader>::Instance();

			if (!resourcePool.HasResource("FPSPassFrag"))
			{
				auto s = resourcePool.CreateResource("FPSPassFrag");

				s->SetStage(ShaderStage::Fragment);
				s->SetSource("src/Assets/Shader/FPSPass.frag");
			}

            auto shader = resourcePool.GetResource("FPSPassFrag");

			m_Pipeline->AddShader(shader->GetStage(), shader->GetRHIResource());
		}

		m_Pipeline->BuildGraphicPipeline();
	}

	void FPSPass::OnRender(Scene* scene)
	{
		const auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdBindPipeline(m_Pipeline);

		cmdList.CmdBindDescriptor(m_DescriptorList);

		cmdList.CmdDrawFullScreenTriangle();

		cmdList.CmdEndRenderPass();
	}

}