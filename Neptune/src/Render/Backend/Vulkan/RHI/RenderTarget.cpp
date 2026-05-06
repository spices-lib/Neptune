/**
* @file RenderTarget.cpp.
* @brief The RenderTarget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderTarget.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Converter.h"
#include "Render/Backend/Vulkan/RHI/CmdList2.h"

namespace Neptune::Vulkan {

	void RenderTarget::CreateRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		CreateColorRenderTarget(info);
	}

	void* RenderTarget::CreateBindingID()
	{
		NEPTUNE_PROFILE_ZONE

		VkDescriptorImageInfo                               imageInfo{};
		imageInfo.imageLayout                             = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfo.imageView                               = m_Image->GetView();
		imageInfo.sampler                                 = m_Image->GetSampler();

		VkDescriptorSetLayoutBinding                        layoutBinding{};
		layoutBinding.binding                             = 0;
		layoutBinding.descriptorType                      = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		layoutBinding.descriptorCount                     = 1;
		layoutBinding.stageFlags                          = VK_SHADER_STAGE_FRAGMENT_BIT;

		m_DescriptorSet.AddBinding(imageInfo, layoutBinding);

		m_DescriptorSet.BuildDescriptorSet();

		m_DescriptorSet.UpdateDescriptorSet();

		return m_DescriptorSet.Handle();
	}

	bool RenderTarget::CopyToRenderTarget(const RHI::RenderTarget* target)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhi = target->GetRHIImpl<RenderTarget>();

		return CopyToRenderTarget(rhi);
	}

	bool RenderTarget::CopyToRenderTarget(RenderTarget* target) const
	{
		NEPTUNE_PROFILE_ZONE

		CmdList2 cmdList(GetContext());

		cmdList.SetGraphicCmdList();

        cmdList.Begin();

		if (m_Image->GetFormat() == VK_FORMAT_G8_B8R8_2PLANE_420_UNORM)
		{
			VkImageCopy                                     region{};
            region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
            region.srcSubresource.layerCount              = m_Image->GetLayerCount();
            region.srcSubresource.baseArrayLayer          = 0;
            region.srcSubresource.mipLevel                = 0;
            region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
            region.dstSubresource.layerCount              = target->m_Image->GetLayerCount();
            region.dstSubresource.baseArrayLayer          = 0;
            region.dstSubresource.mipLevel                = 0;
            region.extent.width                           = m_Image->Width();
            region.extent.height                          = m_Image->Height();
            region.extent.depth                           = 1;

			cmdList.CmdTransitionLayout(m_Image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

            cmdList.CmdTransitionLayout(target->IHandle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

            cmdList.CmdCopyImage(Handle(), target->Handle(), region);

            region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_1_BIT;
            region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_1_BIT;
            region.extent.width                           = m_Image->Width() / 2;
            region.extent.height                          = m_Image->Height() / 2;

            cmdList.CmdCopyImage(Handle(), target->Handle(), region);

			cmdList.CmdTransitionLayout(m_Image, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

            cmdList.CmdTransitionLayout(target->IHandle(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}
		else
		{
			VkImageCopy                                     region{};
			region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
			region.srcSubresource.layerCount              = m_Image->GetLayerCount();
			region.srcSubresource.baseArrayLayer          = 0;
			region.srcSubresource.mipLevel                = 0;
			region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_COLOR_BIT;
			region.dstSubresource.layerCount              = target->m_Image->GetLayerCount();
			region.dstSubresource.baseArrayLayer          = 0;
			region.dstSubresource.mipLevel                = 0;
			region.extent.width                           = m_Image->Width();
			region.extent.height                          = m_Image->Height();
			region.extent.depth                           = 1;

			cmdList.CmdTransitionLayout(target->IHandle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

			cmdList.CmdCopyImage(Handle(), target->Handle(), region);

			cmdList.CmdTransitionLayout(target->IHandle(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		}

        cmdList.End();

        cmdList.SubmitWait();

		return true;
	}

	TextureFormat RenderTarget::GetFormat() const
	{
		NEPTUNE_PROFILE_ZONE

		return ToTextureFormat(m_Image->GetFormat());
	}

	void RenderTarget::CreateColorRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Image = CreateSP<Image>(GetContext());

		{
			VkImageCreateInfo                                  createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			createInfo.imageType                             = ToVkImageType(info.domain);
			createInfo.extent.width                          = info.width;
			createInfo.extent.height                         = info.height;
			createInfo.extent.depth                          = 1;
			createInfo.mipLevels                             = 1;
			createInfo.arrayLayers                           = 1;
			createInfo.format                                = ToVkFormat(info.format);
			createInfo.tiling                                = VK_IMAGE_TILING_OPTIMAL;
			createInfo.initialLayout                         = VK_IMAGE_LAYOUT_UNDEFINED;
			createInfo.usage                                 = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | 
															   VK_IMAGE_USAGE_TRANSFER_DST_BIT |
														       VK_IMAGE_USAGE_SAMPLED_BIT;
			createInfo.sharingMode                           = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.samples                               = VK_SAMPLE_COUNT_1_BIT;
			createInfo.flags                                 = 0;

			m_Image->CreateImage(createInfo, ToVkMemoryPropertyFlags(info.memoryUsage));
		}

		{
			VkImageViewCreateInfo                              createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image                                 = m_Image->Handle();

			createInfo.viewType                              = ToVkImageViewType(info.domain);
			createInfo.format                                = ToVkFormat(info.format);
												       	  
			createInfo.components.r                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a                          = VK_COMPONENT_SWIZZLE_IDENTITY;
												       	  
			createInfo.subresourceRange.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel         = 0;
			createInfo.subresourceRange.levelCount           = 1;
			createInfo.subresourceRange.baseArrayLayer       = 0;
			createInfo.subresourceRange.layerCount           = 1;

			m_Image->CreateImageView(createInfo);
		}

		{
			VkSamplerCreateInfo                                createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			createInfo.magFilter                             = VK_FILTER_LINEAR;
			createInfo.minFilter                             = VK_FILTER_LINEAR;
			createInfo.addressModeU                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.addressModeV                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.addressModeW                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.anisotropyEnable                      = VK_TRUE;

			VkPhysicalDeviceProperties                         properties{};
			vkGetPhysicalDeviceProperties(GetContext().Get<IPhysicalDevice>()->Handle(), &properties);

			createInfo.maxAnisotropy                         = properties.limits.maxSamplerAnisotropy;
			createInfo.borderColor                           = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			createInfo.unnormalizedCoordinates               = VK_FALSE;
			createInfo.compareEnable                         = VK_FALSE;
			createInfo.compareOp                             = VK_COMPARE_OP_ALWAYS;
													         
			createInfo.mipmapMode                            = VK_SAMPLER_MIPMAP_MODE_LINEAR;
			createInfo.mipLodBias                            = 0.0f;
			createInfo.minLod                                = 0;
			createInfo.maxLod                                = 1;

			m_Image->CreateSampler(createInfo);
		}

		m_Image->SetName("RenderTarget");
	}

	void RenderTarget::CreateDepthRenderTarget(const RenderTargetCreateInfo& info)
	{

	}
}

#endif