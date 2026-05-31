#pragma once
#include "Core/Core.h"
#include "Pass.h"
#include <glm/glm.hpp>

namespace Neptune::RHI {

	class DescriptorList;
}

namespace Neptune::Render {

	class PrePass : public Pass
	{
	public:

		PrePass() : Pass() {}
		~PrePass() override = default;

		void OnConstruct() override;

		void OnRender(Scene* scene) override;

		void SetRTSize(const glm::vec2& rtSize) { m_RTSize = rtSize; }

	private:

		SP<RHI::DescriptorList>  m_DescriptorList;

		glm::vec2                m_RTSize{ 100.0f, 100.0f };
	};
}