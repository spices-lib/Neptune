/**
* @file Pipeline.h.
* @brief The Pipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/OpenGL/Core.h"
#include "Render/Frontend/RHI/Pipeline.h"

namespace Neptune::RHI {

	class RenderPass;
	class DescriptorList;
	class Shader;
}

namespace Neptune::OpenGL {

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

	};
}

#endif