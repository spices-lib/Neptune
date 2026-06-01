#pragma once
#include "Core/Core.h"
#include "Pass.h"
#include <glm/glm.hpp>

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
}

namespace Neptune::Render { 

	class BasePass : public Pass
	{
	public:

		BasePass() : Pass() {}
		~BasePass() override = default;

		void OnConstruct() override;

		void OnRender(Scene* scene) override;

		void SetRTSize(const glm::vec2& rtSize) { m_RTSize = rtSize; }

	private:

		SP<RHI::RenderPass>      m_RenderPass;
		SP<RHI::DescriptorList>  m_DescriptorList;
		SP<RHI::Pipeline>        m_Pipeline;
		
		glm::vec2                m_RTSize{ 100.0f, 100.0f };
	};
}