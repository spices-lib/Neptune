/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::CommandBuffer Class.
	* This class defines the Vulkan::Unit::CommandBuffer behaves.
	*/
	class CommandBuffer : public Unit<VkCommandBuffer, VkObjectType::VK_OBJECT_TYPE_COMMAND_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandBuffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandBuffer() override;

		/**
		* @brief Create CommandBuffer.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkCommandBufferAllocateInfo.
		*/
		void CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info);

		/**
		* @brief Begin CommandBuffer.
		*
		* @param[in] info VkCommandBufferBeginInfo.
		*/
		void Begin(const VkCommandBufferBeginInfo& info) const;

		/**
		* @brief End CommandBuffer.
		*/
		void End() const;

		/**
		* @brief Begin RenderPass.
		*
		* @param[in] info VkRenderPassBeginInfo.
		* @param[in] content VkSubpassContents.
		*/
		void BeginRenderPass(const VkRenderPassBeginInfo& info, VkSubpassContents content) const;

		/**
		* @brief End RenderPass.
		*/
		void EndRenderPass() const;

		/**
		* @brief Bind Pipeline.
		* 
		* @param[in] bindPoint VkPipelineBindPoint.
		* @param[in] pipeline VkPipeline.
		*/
		void BindPipeline(VkPipelineBindPoint bindPoint, VkPipeline pipeline) const;

		/**
		* @brief Bind DescriptorSet.
		*
		* @param[in] bindPoint VkPipelineBindPoint.
		* @param[in] layout VkPipelineLayout.
		* @param[in] set .
		* @param[in] descriptorSet VkDescriptorSet.
		*/
		void BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet) const;

		/**
		* @brief Set Viewport.
		*
		* @param[in] viewport VkViewport.
		*/
		void SetViewport(const VkViewport& viewport) const;

		/**
		* @brief Set Scissor.
		*
		* @param[in] scissor VkRect2D.
		*/
		void SetScissor(const VkRect2D& scissor) const;

		/**
		* @brief Draw.
		*
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const;

		/**
		* @brief Begin VideoCoding.
		*
		* @param[in] fn PFN_vkCmdBeginVideoCodingKHR.
		* @param[in] info  VkVideoBeginCodingInfoKHR.
		*/
		void BeginVideoCoding(const PFN_vkCmdBeginVideoCodingKHR& fn, const VkVideoBeginCodingInfoKHR& info) const;

		/**
		* @brief Control VideoCoding.
		*
		* @param[in] fn PFN_vkCmdControlVideoCodingKHR.
		* @param[in] info VkVideoCodingControlInfoKHR.
		*/
		void ControlVideoCoding(const PFN_vkCmdControlVideoCodingKHR& fn, const VkVideoCodingControlInfoKHR& info) const;

		/**
		* @brief Decode Video.
		*
		* @param[in] fn PFN_vkCmdDecodeVideoKHR.
		* @param[in] info VkVideoDecodeInfoKHR.
		*/
		void DecodeVideo(const PFN_vkCmdDecodeVideoKHR& fn, const VkVideoDecodeInfoKHR& info) const;

		/**
		* @brief End Video Coding.
		*
		* @param[in] fn PFN_vkCmdEndVideoCodingKHR.
		* @param[in] info VkVideoEndCodingInfoKHR.
		*/
		void EndVideoCoding(const PFN_vkCmdEndVideoCodingKHR& fn, const VkVideoEndCodingInfoKHR& info) const;

		/**
		* @brief Optical Flow Execute.
		*
		* @param[in] fn PFN_vkCmdOpticalFlowExecuteNV.
		* @param[in] session VkOpticalFlowSessionNV.
		* @param[in] info VkOpticalFlowExecuteInfoNV.
		*/
		void OpticalFlowExecute(const PFN_vkCmdOpticalFlowExecuteNV& fn, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV& info) const;

		/**
		* @brief Copy Image.
		*
		* @param[in] src VkImage.
		* @param[in] dst VkImage.
		* @param[in] region VkImageCopy.
		*/
		void CopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const;

		/**
		* @brief Pipeline Barrier.
		*
		* @param[in] srcMask VkPipelineStageFlags.
		* @param[in] dstMask VkPipelineStageFlags.
		* @param[in] barrier VkImageMemoryBarrier.
		*/
		void PipelineBarrier(VkPipelineStageFlags srcMask, VkPipelineStageFlags dstMask, const VkImageMemoryBarrier& barrier) const;

		/**
		* @brief Begin Query.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] index .
		* @param[in] flag VkQueryControlFlags.
		*/
		void BeginQuery(VkQueryPool pool, uint32_t index, VkQueryControlFlags flag) const;

		/**
		* @brief End Query.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] index .
		*/
		void EndQuery(VkQueryPool pool, uint32_t index) const;

		/**
		* @brief Write TimeStamp.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] index .
		*/
		void WriteTimeStamp(VkQueryPool pool, uint32_t index) const;

		/**
		* @brief Reset TimeStamp.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] count .
		*/
		void ResetQueryPool(VkQueryPool pool, uint32_t count) const;

	private:

		VkDevice m_Device           = VK_NULL_HANDLE;     // @brief VkDevice.
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;     // @brief VkCommandPool.

	};
}

#endif