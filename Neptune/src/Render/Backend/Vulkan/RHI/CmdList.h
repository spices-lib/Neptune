/**
* @file CmdList.h.
* @brief The CmdList Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Render/Frontend/RHI/CmdList.h"

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
}

namespace Neptune::Vulkan {

	namespace Resource {

		class VideoSession;
		class Image;
		class QueryPool;
	}

	class RenderPass;
	
	/**
	* @brief Vulkan::CmdList Class.
	* This class defines the Vulkan::CmdList behaves.
	*/
	class CmdList : public ContextAccessor, public RHI::RHICmdList::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit CmdList(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~CmdList() override = default;

	public:

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*
		* @param[in] clock Clock.
		*/
		void SetGraphicCmdList(const Data::Clock& clock) override;

		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<RHI::RenderPass>& renderPass) override;

		/**
		* @brief Interface of DrawSlate.
		*/
		void CmdDrawSlate() const override;

		/**
		* @brief Interface of BeginRenderPass.
		*/
		void CmdBeginRenderPass() const override;

		/**
		* @brief Interface of EndRenderPass.
		*/
		void CmdEndRenderPass() const override;

		/**
		* @brief Interface of BindDescriptor.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void CmdBindDescriptor(const SP<RHI::DescriptorList>& descriptorList) const override;

		/**
		* @brief Interface of BindPipeline.
		*
		* @param[in] pipeline Pipeline.
		*/
		void CmdBindPipeline(const SP<RHI::Pipeline>& pipeline) override;

		/**
		* @brief Interface of DrawFullScreenTriangle.
		*/
		void CmdDrawFullScreenTriangle() const override;

		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::vec2& viewPortSize) const override;

	public:

		/**
		* @brief Set QueryPool.
		*
		* @param[in] queryPool QueryPool.
		*/
		void SetQueryPool(const SP<Resource::QueryPool>& queryPool);

		/**
		* @brief Copy Image.
		*
		* @param[in] src VkImage.
		* @param[in] dst VkImage.
		* @param[in] region VkImageCopy.
		*/
		void CmdCopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const;

		/**
		* @brief Pipeline Barrier.
		*
		* @param[in] srcMask VkPipelineStageFlags.
		* @param[in] dstMask VkPipelineStageFlags.
		* @param[in] barrier VkImageMemoryBarrier.
		*/
		void CmdPipelineBarrier(VkPipelineStageFlags srcMask, VkPipelineStageFlags dstMask, const VkImageMemoryBarrier& barrier) const;

		/**
		* @brief Transition Layout.
		*
		* @param[in] image Image.
		* @param[in] newLayout VkImageLayout.
		*/
		void CmdTransitionLayout(SP<Resource::Image> image, VkImageLayout newLayout) const;

		/**
		* @brief Begin Query.
		*
		* @param[in] index .
		*/
		void CmdBeginQuery(uint32_t index) const;

		/**
		* @brief End Query.
		*
		* @param[in] index .
		*/
		void CmdEndQuery(uint32_t index) const;

		/**
		* @brief Write TimeStamp.
		*
		* @param[in] index .
		*/
		void CmdWriteTimeStamp(uint32_t index) const;

		/**
		* @brief Reset QueryPool.
		*/
		void CmdResetQueryPool() const;

	protected:

		uint32_t                      m_FrameIndex     = 0;                                     // @brief Frame index.
		uint32_t                      m_ImageIndex     = 0;                                     // @brief Image index.

		SP<Unit::CommandBuffer>       m_CommandBuffer  = nullptr;                               // @brief CommandBuffer reference.
		const RenderPass*             m_RenderPass     = nullptr;                               // @brief RenderPass reference.
		const Resource::QueryPool*    m_QueryPool      = nullptr;                               // @brief QueryPool reference.
		VkPipelineBindPoint           m_BindPoint      = VK_PIPELINE_BIND_POINT_MAX_ENUM;       // @brief VkPipelineBindPoint.
		VkPipelineLayout              m_PipelineLayout = VK_NULL_HANDLE;                        // @brief VkPipelineLayout.
	};
}

#endif