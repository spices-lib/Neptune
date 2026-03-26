#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Pipeline.h"
#include "Render/Backend/Vulkan/Unit/PipelineLayout.h"
#include "Render/Frontend/RHI/Pipeline.h"

namespace Neptune::RHI {

	class RenderPass;
	class DescriptorList;
	class Shader;
}

namespace Neptune::Vulkan {

	class Pipeline : public ContextAccessor, public RHI::RHIPipeline::Impl
	{
	public:

		Pipeline(Context& context) : ContextAccessor(context) {}
		~Pipeline() override = default;

		const VkPipeline& Handle() const { return m_Pipeline.GetHandle(); }

		VkPipelineBindPoint GetBindPoint() const { return m_BindPoint; }

		const VkPipelineLayout& GetPipelineLayout() const { return m_PipelineLayout.GetHandle(); }

		void SetDefault() override;

		void SetRenderPass(SP<RHI::RenderPass> renderPass) override;

		void SetVertexAttributeLayout() override;

		void SetDescriptorList(SP<RHI::DescriptorList> descriptorList) override;

		void SetCullMode(CullMode mode) override;

		void AddShader(ShaderStage stage, SP<RHI::Shader> shader) override;

		void BuildGraphicPipeline() override;

	private:

		Unit::Pipeline                                   m_Pipeline;
		VkPipelineBindPoint                              m_BindPoint;

		VkPipelineInputAssemblyStateCreateInfo           m_InputAssemblyInfo{};
		VkPipelineViewportStateCreateInfo                m_ViewportInfo{};
		VkPipelineRasterizationStateCreateInfo           m_RasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo             m_MultisampleInfo{};
		VkPipelineColorBlendStateCreateInfo              m_ColorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo            m_DepthStencilInfo{};
		std::vector<VkDynamicState>                      m_DynamicStateEnables{};
		VkPipelineDynamicStateCreateInfo                 m_DynamicStateInfo{};
		std::vector<VkVertexInputBindingDescription>     m_BindingDescriptions{};
		std::vector<VkVertexInputAttributeDescription>   m_AttributeDescriptions{};
		VkRenderPass                                     m_RenderPass{};
		std::vector<VkPipelineShaderStageCreateInfo>     m_ShaderStages{};

		Unit::PipelineLayout                             m_PipelineLayout{};

		VkViewport                                       m_Viewport{};
		VkRect2D                                         m_Scissor{};
	};
}