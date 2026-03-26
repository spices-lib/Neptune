#include "Pchheader.h"
#include "PrePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/DescriptorList.h"
#include "Render/Frontend/RHI/CmdList.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Mesh/Mesh.h"
#include "Assets/Shader/Header/ShaderCore.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"

namespace Neptune::Render {

	void PrePass::OnConstruct()
	{
		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->SetSharedLayout();
		m_DescriptorList->AddUniformBuffer(0, 0, sizeof(ShaderCore::View));
		m_DescriptorList->AddUniformBuffer(0, 1, sizeof(ShaderCore::Input));
		m_DescriptorList->Build();
	}

	void PrePass::OnRender(Scene* scene)
	{
		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		ShaderCore::View view{};

		view.sceneTextureSize = {
			m_RTSize.x,
			m_RTSize.y,
			1.0f / m_RTSize.x,
			1.0f / m_RTSize.y
		};

		m_DescriptorList->UpdateUniformBuffer(0, 0, &view);

		ShaderCore::Input      input{};
		input.engineTime     = clock.m_EngineTime;
		input.frameTime      = clock.m_FrameTime;

		m_DescriptorList->UpdateUniformBuffer(0, 1, &input);
	}

}