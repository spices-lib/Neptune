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

	class FPSPass : public Pass
	{
	public:

		FPSPass() : Pass() {}
		~FPSPass() override = default;

		void OnConstruct() override;

		void OnRender(Scene* scene) override;

	private:

		SP<RHI::RenderPass>      m_RenderPass;
		SP<RHI::DescriptorList>  m_DescriptorList;
		SP<RHI::Pipeline>        m_Pipeline;
	};
}