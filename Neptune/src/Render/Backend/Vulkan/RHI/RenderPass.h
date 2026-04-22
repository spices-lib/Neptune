/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/RenderPass.h"
#include "Render/Backend/Vulkan/Unit/FrameBuffer.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Render/Frontend/RHI/RenderPass.h"

#include <vector>
#include <optional>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::RenderPass Class.
	* This class defines the Vulkan::RenderPass behaves.
	*/
	class RenderPass : public ContextAccessor, public RHI::RHIRenderPass::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit RenderPass(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~RenderPass() override = default;

	public:

		/**
		* @brief Interface of Add SwapChain Attachment.
		*/
		void AddSwapChainAttachment() override;

		/**
		* @brief Interface of Add Color Attachment.
		*
		* @param[in] renderTarget RenderTarget.
		* @param[in] info RenderTargetAttachmentInfo.
		*/
		void AddColorAttachment(SP<RHI::RenderTarget> renderTarget, const RenderTargetAttachmentInfo& info) override;

		/**
		* @brief Interface of Build RenderPass.
		*
		* @param[in] count Flight Frames.
		*/
		void Build(uint32_t count = MaxFrameInFlight) override;

	public:

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const VkRenderPass& Handle() const { return m_RenderPass.GetHandle(); }

		/**
		* @brief Begin RenderPass.
		*
		* @param[in] commandBuffer CommandBuffer.
		* @param[in] frameBufferIndex .
		*/
		void BeginRenderPass(const Unit::CommandBuffer* commandBuffer, uint32_t frameBufferIndex) const;

		/**
		* @brief Get ColorBlends.
		*
		* @return Returns VkPipelineColorBlendAttachmentState.
		*/
		const std::vector<VkPipelineColorBlendAttachmentState>& GetColorBlends() const { return m_ColorBlends; }

	private:

		/**
		* @brief Store Extent.
		*
		* @param[in] extent VkExtent2D.
		*/
		void StoreExtent(const VkExtent2D& extent);

	private:

		Unit::RenderPass                                  m_RenderPass;                      // @brief This RenderPass.
		std::vector<SP<Unit::FrameBuffer>>                m_FrameBuffers;                    // @brief Container of FrameBuffer.

		std::vector<VkAttachmentDescription>              m_AttachmentDescriptions;          // @brief VkAttachmentDescription.
		std::vector<VkAttachmentReference>                m_ColorAttachmentReference;        // @brief VkAttachmentReference.
		std::vector<VkPipelineColorBlendAttachmentState>  m_ColorBlends;					 // @brief VkPipelineColorBlendAttachmentState.
		std::vector<VkClearValue>                         m_ClearValues;					 // @brief VkClearValue.
		std::vector<VkImageView>                          m_ImageViews;						 // @brief VkImageView.
		std::optional<VkExtent2D>                         m_Extent;							 // @brief VkExtent2D.
	};
}

#endif