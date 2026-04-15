/**
* @file Pipeline.h.
* @brief The Pipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

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

	/**
	* @brief Vulkan::Pipeline Class.
	* This class defines the Vulkan::Pipeline behaves.
	*/
	class Pipeline : public ContextAccessor, public RHI::RHIPipeline::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Pipeline(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Pipeline() override = default;

	public:

		/**
		* @brief Interface of Set Default Pipeline.
		*/
		void SetDefault() override;

		/**
		* @brief Interface of Set RenderPass.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(SP<RHI::RenderPass> renderPass) override;
		
		/**
		* @brief Interface of Set DescriptorList.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void SetDescriptorList(SP<RHI::DescriptorList> descriptorList) override;

		/**
		* @brief Interface of Set VertexAttributeLayout.
		*/
		void SetVertexAttributeLayout() override;
		
		/**
		* @brief Interface of Set CullMode.
		*
		* @param[in] mode CullMode.
		*/
		void SetCullMode(CullMode mode) override;

		/**
		* @brief Interface of Add Shader.
		*
		* @param[in] stage ShaderStage.
		* @param[in] shader Shader.
		*/
		void AddShader(ShaderStage stage, SP<RHI::Shader> shader) override;

		/**
		* @brief Interface of Build GraphicPipeline.
		*/
		void BuildGraphicPipeline() override;

	public:

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Pipeline::Handle& Handle() const { return m_Pipeline.GetHandle(); }

		/**
		* @brief Get BindPoint.
		*
		* @return Returns BindPoint.
		*/
		VkPipelineBindPoint GetBindPoint() const { return m_BindPoint; }

		/**
		* @brief Get PipelineLayout Unit Handle.
		*
		* @return Returns PipelineLayout Unit Handle.
		*/
		const Unit::PipelineLayout::Handle& GetPipelineLayout() const { return m_PipelineLayout.GetHandle(); }

	private:

		Unit::Pipeline                                   m_Pipeline;                          // @brief This Pipeline.
		VkPipelineBindPoint                              m_BindPoint;                         // @brief VkPipelineBindPoint.

		VkPipelineInputAssemblyStateCreateInfo           m_InputAssemblyInfo{};               // @brief VkPipelineInputAssemblyStateCreateInfo.
		VkPipelineViewportStateCreateInfo                m_ViewportInfo{};                    // @brief VkPipelineViewportStateCreateInfo.
		VkPipelineRasterizationStateCreateInfo           m_RasterizationInfo{};               // @brief VkPipelineRasterizationStateCreateInfo.
		VkPipelineMultisampleStateCreateInfo             m_MultisampleInfo{};				  // @brief VkPipelineMultisampleStateCreateInfo.
		VkPipelineColorBlendStateCreateInfo              m_ColorBlendInfo{};				  // @brief VkPipelineColorBlendStateCreateInfo.
		VkPipelineDepthStencilStateCreateInfo            m_DepthStencilInfo{};				  // @brief VkPipelineDepthStencilStateCreateInfo.
		std::vector<VkDynamicState>                      m_DynamicStateEnables{};			  // @brief VkDynamicState.
		VkPipelineDynamicStateCreateInfo                 m_DynamicStateInfo{};				  // @brief VkPipelineDynamicStateCreateInfo.
		std::vector<VkVertexInputBindingDescription>     m_BindingDescriptions{};			  // @brief VkVertexInputBindingDescription.
		std::vector<VkVertexInputAttributeDescription>   m_AttributeDescriptions{};			  // @brief VkVertexInputAttributeDescription.
		VkRenderPass                                     m_RenderPass{};					  // @brief VkRenderPass.
		std::vector<VkPipelineShaderStageCreateInfo>     m_ShaderStages{};                    // @brief VkPipelineShaderStageCreateInfo.

		Unit::PipelineLayout                             m_PipelineLayout{};                  // @brief This PipelineLayout.

		VkViewport                                       m_Viewport{};                        // @brief VkViewport.
		VkRect2D                                         m_Scissor{};                         // @brief VkRect2D.
	};
}

#endif