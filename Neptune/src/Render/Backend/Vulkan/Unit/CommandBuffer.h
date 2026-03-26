#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	class CommandBuffer : public Unit<VkCommandBuffer, VkObjectType::VK_OBJECT_TYPE_COMMAND_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		CommandBuffer() : Unit() {}

		~CommandBuffer() override;

		void CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info);

		void Begin(const VkCommandBufferBeginInfo& info) const;

		void End() const;

		void BeginRenderPass(const VkRenderPassBeginInfo& info, VkSubpassContents content) const;

		void EndRenderPass() const;

		void BindPipeline(VkPipelineBindPoint bindPoint, VkPipeline pipeline) const;

		void BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet) const;

		void SetViewport(const VkViewport& viewport);

		void SetScissor(const VkRect2D& scissor);

		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const;

		void BeginVideoCoding(const PFN_vkCmdBeginVideoCodingKHR& fn, const VkVideoBeginCodingInfoKHR& info) const;

		void ControlVideoCoding(const PFN_vkCmdControlVideoCodingKHR& fn, const VkVideoCodingControlInfoKHR& info) const;

		void DecodeVideo(const PFN_vkCmdDecodeVideoKHR& fn, const VkVideoDecodeInfoKHR& info) const;

		void EndVideoCoding(const PFN_vkCmdEndVideoCodingKHR& fn, const VkVideoEndCodingInfoKHR& info) const;

		void OpticalFlowExecute(const PFN_vkCmdOpticalFlowExecuteNV& fn, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV& info) const;

		void CopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const;

		void PipelineBarrier(VkPipelineStageFlags srcMask, VkPipelineStageFlags dstMask, const VkImageMemoryBarrier& barrier) const;

		void BeginQuery(VkQueryPool pool, uint32_t index, VkQueryControlFlags flag);

		void EndQuery(VkQueryPool pool, uint32_t index);

		void WriteTimeStamp(VkQueryPool pool, uint32_t index);

		void ResetQueryPool(VkQueryPool pool, uint32_t count);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
	};
}