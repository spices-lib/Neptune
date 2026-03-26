#include "Pchheader.h"
#include "SlatePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/CmdList.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"

namespace Neptune::Render {

	void SlatePass::OnConstruct()
	{
		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddSwapChainAttachment();
		m_RenderPass->Build();
	}

	void SlatePass::OnRender(Scene* scene)
	{
		const auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdDrawSlate();

		cmdList.CmdEndRenderPass();
	}
}