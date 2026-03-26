#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Render/Frontend/RHI/CmdList.h"

namespace Neptune::Data {

	struct Clock;

}

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
}

namespace Neptune::Vulkan {

	class RenderPass;
	class VideoSession;
	class Image;
	class QueryPool;

	class CmdList : public ContextAccessor, public RHI::RHICmdList::Impl
	{
	public:

		CmdList(Context& context) : ContextAccessor(context) {}
		~CmdList() override = default;

		void SetGraphicCmdList(const Data::Clock& clock) override;

		void SetRenderPass(SP<RHI::RenderPass> renderPass) override;

		void SetQueryPool(SP<QueryPool> queryPool);

		void CmdDrawSlate() const override;

		void CmdBeginRenderPass() const override;

		void CmdEndRenderPass() const override;

		void CmdBindDescriptor(SP<RHI::DescriptorList> descriptorList) const override;

		void CmdBindPipeline(SP<RHI::Pipeline> pipeline) override;

		void CmdDrawFullScreenTriangle() const override;

		void CmdSetViewport(const glm::vec2& viewPortSize) const override;

		void CmdCopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const;

		void CmdPipelineBarrier(VkPipelineStageFlags srcMask,VkPipelineStageFlags dstMask, const VkImageMemoryBarrier& barrier) const;

		void CmdTransitionLayout(SP<Image> image, VkImageLayout newLayout) const;

		void CmdBeginQuery(uint32_t index) const;

		void CmdEndQuery(uint32_t index) const;

		void CmdWriteTimeStamp(uint32_t index) const;

		void CmdResetQueryPool() const;

	protected:

		uint32_t                   m_FrameIndex     = 0;
		uint32_t                   m_ImageIndex     = 0;

		SP<Unit::CommandBuffer>    m_CommandBuffer  = nullptr;
		SP<RenderPass>             m_RenderPass     = nullptr;
		SP<QueryPool>              m_QueryPool      = nullptr;
		VkPipelineBindPoint        m_BindPoint      = VK_PIPELINE_BIND_POINT_MAX_ENUM;
		VkPipelineLayout           m_PipelineLayout = VK_NULL_HANDLE;
	};
}