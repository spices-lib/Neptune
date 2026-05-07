/**
* @file CmdList.cpp.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "CmdList.h"
#include "Render/Backend/Vulkan/Infrastructure/CommandBuffer.h"
#include "Render/Backend/Vulkan/RHI/RenderPass.h"
#include "Render/Backend/Vulkan/RHI/Pipeline.h"
#include "Render/Backend/Vulkan/RHI/DescriptorList.h"
#include "Render/Backend/Vulkan/Resource/VideoSession.h"
#include "Render/Backend/Vulkan/Resource/QueryPool.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Data/Clock.h"

namespace Neptune::Vulkan {

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE

		m_FrameIndex = clock.m_FrameIndex;
		m_ImageIndex = clock.m_ImageIndex;

		m_CommandBuffer = GetContext().Get<IGraphicCommandBuffer>()->IHandle(m_FrameIndex);

		m_BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	}

	void CmdList::CmdDrawSlate() const
	{
		NEPTUNE_PROFILE_ZONE

		/*const ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_CommandBuffer->GetHandle());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}*/
	}

	void CmdList::CmdBeginRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->BeginRenderPass(m_CommandBuffer.get(), m_ImageIndex);
	}

	void CmdList::CmdEndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->EndRenderPass();
	}

	void CmdList::CmdBindDescriptor(const SP<RHI::DescriptorList>& descriptorList) const
	{
		NEPTUNE_PROFILE_ZONE

		auto sharedRhi = dynamic_cast<const DescriptorList*>(descriptorList->GetSharedImpl());

		auto rhi = descriptorList->GetRHIImpl<DescriptorList>();

		for (const auto& [fst, snd] : sharedRhi->GetSets())
		{
			m_CommandBuffer->BindDescriptorSet(m_BindPoint, m_PipelineLayout, fst, snd->Handle());
		}

		for (const auto& [fst, snd] : rhi->GetSets())
		{
			m_CommandBuffer->BindDescriptorSet(m_BindPoint, m_PipelineLayout, fst, snd->Handle());
		}
	}

	void CmdList::CmdBindPipeline(const SP<RHI::Pipeline>& pipeline)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhi = pipeline->GetRHIImpl<Pipeline>();

		assert(rhi->GetBindPoint() == m_BindPoint);

		m_PipelineLayout = rhi->GetPipelineLayout();

		m_CommandBuffer->BindPipeline(rhi->GetBindPoint(), rhi->Handle());
	}

	void CmdList::CmdDrawFullScreenTriangle() const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->Draw(3, 1, 0, 0);
	}

	void CmdList::CmdSetViewport(const glm::vec2& viewPortSize) const
	{
		NEPTUNE_PROFILE_ZONE

		VkViewport                     viewport{};
		viewport.x                  =  0.0f;
		viewport.y                  =  viewPortSize.y;
		viewport.width              =  viewPortSize.x;
		viewport.height             = -viewPortSize.y;
		viewport.minDepth           =  0.0f;
		viewport.maxDepth           =  1.0f;

		VkExtent2D                    extent;
		extent.width                = viewPortSize.x;
		extent.height               = viewPortSize.y;

		VkRect2D                      scissor{};
		scissor.offset              = { 0, 0 };
		scissor.extent              = extent;
			
		m_CommandBuffer->SetViewport(viewport);

		m_CommandBuffer->SetScissor(scissor);
	}

	void CmdList::SetRenderPass(const SP<RHI::RenderPass>& renderPass)
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass = renderPass->GetRHIImpl<RenderPass>();
	}

	void CmdList::SetQueryPool(const SP<Resource::QueryPool>& queryPool)
	{
		NEPTUNE_PROFILE_ZONE

		m_QueryPool = queryPool.get();
	}

	void CmdList::CmdCopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->CopyImage(src, dst, region);
	}

	void CmdList::CmdPipelineBarrier(VkPipelineStageFlags srcMask, VkPipelineStageFlags dstMask, const VkImageMemoryBarrier& barrier) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->PipelineBarrier(srcMask, dstMask, barrier);
	}

	void CmdList::CmdTransitionLayout(SP<Resource::Image> image, VkImageLayout newLayout) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		auto oldLayout = image->GetLayout();

		VkImageMemoryBarrier                           barrier{};
		barrier.sType                                = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout                            = oldLayout;
		barrier.newLayout                            = newLayout;
		barrier.srcQueueFamilyIndex                  = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex                  = VK_QUEUE_FAMILY_IGNORED;
		barrier.image                                = image->Handle();
		barrier.subresourceRange.aspectMask          = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel        = 0;
		barrier.subresourceRange.levelCount          = 1;
		barrier.subresourceRange.baseArrayLayer      = 0;
		barrier.subresourceRange.layerCount          = image->GetLayerCount();
		barrier.srcAccessMask                        = 0;
		barrier.dstAccessMask                        = 0;

		if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			// Used for copying
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;

			// Used for copying
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;

			// Used for copying
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) 
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			// Used for copying
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			// Used for sampling.
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			// From a copying stage to...
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;

			// The fragment stage.
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			// From a copying stage to...
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;

			// The fragment stage.
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) 
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		}
		else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_GENERAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_IMAGE_ASPECT_NONE;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		}
		else 
		{
			NEPTUNE_CORE_WARN("Unsupported Vulkan Image Layout Transition!");
			return;
		}
		if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) 
		{
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

			if (image->GetFormat() == VK_FORMAT_D32_SFLOAT_S8_UINT || image->GetFormat() == VK_FORMAT_D24_UNORM_S8_UINT)
			{
				barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
			}
		}
		else 
		{
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		}

		CmdPipelineBarrier(sourceStage, destinationStage, barrier);

		image->SetLayout(newLayout);
	}

	void CmdList::CmdBeginQuery(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->BeginQuery(m_QueryPool->Handle(), index, m_QueryPool->Flag());
	}

	void CmdList::CmdEndQuery(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->EndQuery(m_QueryPool->Handle(), index);
	}

	void CmdList::CmdWriteTimeStamp(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->WriteTimeStamp(m_QueryPool->Handle(), index);
	}

	void CmdList::CmdResetQueryPool() const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->ResetQueryPool(m_QueryPool->Handle(), m_QueryPool->Count());
	}
}

#endif