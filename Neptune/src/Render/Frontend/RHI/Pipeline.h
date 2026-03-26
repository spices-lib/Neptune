#pragma once
#include "Core/Core.h"
#include "Resource/Mesh/Mesh.h"
#include "Resource/Shader/Shader.h"
#include "RHI.h"

namespace Neptune::RHI {

	using RHIPipeline = RHI<ERHI::Pipeline>;

	template<>
	class RHIPipeline::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void SetDefault() = 0;
		virtual void SetRenderPass(SP<class RenderPass> renderPass) = 0;
		virtual void SetDescriptorList(SP<class DescriptorList> descriptorList) = 0;
		virtual void SetVertexAttributeLayout() = 0;
		virtual void SetCullMode(CullMode mode) = 0;
		virtual void AddShader(ShaderStage stage, SP<class Shader> shader) = 0;
		virtual void BuildGraphicPipeline() = 0;
	};

	class Pipeline : public RHIPipeline
	{
	public:

		Pipeline() = default;
		~Pipeline() override = default;

		void SetDefault() const { RHIPipeline::m_Impl->SetDefault(); }

		void SetRenderPass(SP<class RenderPass> renderPass) const { RHIPipeline::m_Impl->SetRenderPass(renderPass); }

		void SetVertexAttributeLayout() const { RHIPipeline::m_Impl->SetVertexAttributeLayout(); }

		void SetDescriptorList(SP<class DescriptorList> descriptorList) const { RHIPipeline::m_Impl->SetDescriptorList(descriptorList); }

		void SetCullMode(CullMode mode) const { RHIPipeline::m_Impl->SetCullMode(mode); }

		void AddShader(ShaderStage stage, SP<class Shader> shader) const { RHIPipeline::m_Impl->AddShader(stage, shader); }

		void BuildGraphicPipeline() const { RHIPipeline::m_Impl->BuildGraphicPipeline(); }

	};

	
}