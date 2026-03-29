/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "CommandBuffer.h"
#include <functional>

namespace Neptune::Vulkan::Unit {

	CommandBuffer::~CommandBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkFreeCommandBuffers(m_Device, m_CommandPool, 1, &m_Handle);
	}

	void CommandBuffer::CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device && info.commandPool);

		m_Device = device;
		m_CommandPool = info.commandPool;

		VK_CHECK(vkAllocateCommandBuffers(m_Device, &info, &m_Handle))
	}

	void CommandBuffer::Begin(const VkCommandBufferBeginInfo& info) const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkBeginCommandBuffer(m_Handle, &info))
	}

	void CommandBuffer::End() const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkEndCommandBuffer(m_Handle))
	}

	void CommandBuffer::BeginRenderPass(const VkRenderPassBeginInfo& info, VkSubpassContents content) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBeginRenderPass(m_Handle, &info, content);
	}

	void CommandBuffer::EndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdEndRenderPass(m_Handle);
	}

	void CommandBuffer::BindPipeline(VkPipelineBindPoint bindPoint, VkPipeline pipeline) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBindPipeline(m_Handle, bindPoint, pipeline);
	}

	void CommandBuffer::BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBindDescriptorSets(m_Handle, bindPoint, layout, set, 1, &descriptorSet, 0, nullptr);
	}

	void CommandBuffer::SetViewport(const VkViewport& viewport) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdSetViewport(m_Handle, 0, 1, &viewport);
	}

	void CommandBuffer::SetScissor(const VkRect2D& scissor) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdSetScissor(m_Handle, 0, 1, &scissor);
	}

	void CommandBuffer::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdDraw(m_Handle, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void CommandBuffer::BeginVideoCoding(const PFN_vkCmdBeginVideoCodingKHR& fn, const VkVideoBeginCodingInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::ControlVideoCoding(const PFN_vkCmdControlVideoCodingKHR& fn, const VkVideoCodingControlInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::DecodeVideo(const PFN_vkCmdDecodeVideoKHR& fn, const VkVideoDecodeInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::EndVideoCoding(const PFN_vkCmdEndVideoCodingKHR& fn, const VkVideoEndCodingInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::OpticalFlowExecute(const PFN_vkCmdOpticalFlowExecuteNV& fn, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, session, &info);
	}

	void CommandBuffer::CopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdCopyImage(m_Handle, src, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	}

	void CommandBuffer::PipelineBarrier(VkPipelineStageFlags srcMask, VkPipelineStageFlags dstMask, const VkImageMemoryBarrier& barrier) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdPipelineBarrier(m_Handle, srcMask, dstMask, 0, 0, nullptr, 0, nullptr, 1, &barrier);
	}

	void CommandBuffer::BeginQuery(VkQueryPool pool, uint32_t index, VkQueryControlFlags flag) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBeginQuery(m_Handle, pool, index, flag);
	}

	void CommandBuffer::EndQuery(VkQueryPool pool, uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdEndQuery(m_Handle, pool, index);
	}

	void CommandBuffer::WriteTimeStamp(VkQueryPool pool, uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdWriteTimestamp2(m_Handle, VK_PIPELINE_STAGE_2_NONE, pool, index);
	}

	void CommandBuffer::ResetQueryPool(VkQueryPool pool, uint32_t count) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdResetQueryPool(m_Handle, pool, 0, count);
	}
}