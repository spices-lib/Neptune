/**
* @file Image.cpp.
* @brief The Image Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Image.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/RHI/CmdList2.h"

namespace Neptune::Vulkan {

	void Image::SetImage(Unit::Image::Handle image)
	{
		NEPTUNE_PROFILE_ZONE

		m_Image.SetHandle(image);

		DEBUGUTILS_SETOBJECTNAME(m_Image, "Image")
	}

	void Image::CreateImage(const VkImageCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		NEPTUNE_PROFILE_ZONE

		m_Format                     = info.format;
		m_Layout                     = info.initialLayout;
		m_LayerCount                 = info.arrayLayers;
		m_Width                      = info.extent.width;
		m_Height                     = info.extent.height;
		 
		GetContext().Has<IMemoryAllocator>() ? 
		m_Image.CreateImage(GetContext().Get<IMemoryAllocator>()->Handle(), info, properties) : 
		m_Image.CreateImage(GetContext().Get<IPhysicalDevice>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties);

		DEBUGUTILS_SETOBJECTNAME(m_Image, "Image")
	}

	void Image::CreateImageView(const VkImageViewCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(m_Image.GetHandle());

		m_ImageView.CreateImageView(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_ImageView, "ImageView")
	}

	void Image::CreateSampler(VkSamplerCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_ImageSampler.CreateSampler(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, "ImageSampler")
	}

	void Image::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Image, name + "Image")
		DEBUGUTILS_SETOBJECTNAME(m_ImageView, name + "ImageView")
		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, name + "ImageSampler")
	}

	void Image::TransitionLayout(VkImageLayout newLayout)
	{
		NEPTUNE_PROFILE_ZONE

		VkPipelineStageFlags sourceStage;
		VkPipelineStageFlags destinationStage;

		VkImageMemoryBarrier                           barrier{};
		barrier.sType                                = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout                            = m_Layout;
		barrier.newLayout                            = newLayout;
		barrier.srcQueueFamilyIndex                  = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex                  = VK_QUEUE_FAMILY_IGNORED;
		barrier.image                                = Handle();
		barrier.subresourceRange.aspectMask          = VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel        = 0;
		barrier.subresourceRange.levelCount          = 1;
		barrier.subresourceRange.baseArrayLayer      = 0;
		barrier.subresourceRange.layerCount          = m_LayerCount;
		barrier.srcAccessMask                        = 0;
		barrier.dstAccessMask                        = 0;

		if (m_Layout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			// Used for copying
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (m_Layout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			// Used for copying
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		}
		else if (m_Layout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			// Don't care what stage the pipeline is in at the start.
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			// Used for sampling.
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (m_Layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			// From a copying stage to...
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;

			// The fragment stage.
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (m_Layout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		{
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			// From a copying stage to...
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;

			// The fragment stage.
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		}
		else if (m_Layout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		{
			barrier.srcAccessMask = 0;
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		}
		else if (m_Layout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_GENERAL)
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

			if (m_Format == VK_FORMAT_D32_SFLOAT_S8_UINT || m_Format == VK_FORMAT_D24_UNORM_S8_UINT)
			{
				barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
			}
		}
		else 
		{
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		}

		CmdList2 cmdList(GetContext());

		cmdList.SetGraphicCmdList();

		cmdList.Begin();

		cmdList.CmdPipelineBarrier(sourceStage, destinationStage, barrier);

		cmdList.End();

		cmdList.SubmitWait();

		SetLayout(newLayout);
	}
}

#endif