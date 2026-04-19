/**
* @file SlatePass.cpp.
* @brief The SlatePass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SlatePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/CmdList.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::Render {

	void SlatePass::OnConstruct()
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddSwapChainAttachment();
		m_RenderPass->Build();
	}

	void SlatePass::OnRender(Scene* scene)
	{
		NEPTUNE_PROFILE_ZONE

		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		RHI::CmdList cmdList;

		cmdList.SetGraphicCmdList(clock);

		cmdList.SetRenderPass(m_RenderPass);

		cmdList.CmdBeginRenderPass();

		cmdList.CmdDrawSlate();

		cmdList.CmdEndRenderPass();
	}
}