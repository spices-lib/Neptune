/**
* @file VideoSession.cpp.
* @brief The VideoSession Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "VideoSession.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/Resource/DecodeBuffer.h"
#include "Render/Backend/Vulkan/Resource/QueryPool.h"
#include "Core/Math/Math.h"

namespace Neptune::Vulkan {

	namespace {
	
		constexpr uint32_t MaxStdVPSCount = 16;
		constexpr uint32_t MaxStdSPSCount = 32;
		constexpr uint32_t MaxStdPPSCount = 256;
	}					   
	
	VideoSession::VideoSession(Context& context)
		: ContextAccessor(context)
		, m_DPB(context)
	{
		NEPTUNE_PROFILE_ZONE

		m_Session.SetFunctor(
			GetContext().Get<IFunctions>()->vkCreateVideoSessionKHR, 
			GetContext().Get<IFunctions>()->vkDestroyVideoSessionKHR,
			GetContext().Get<IFunctions>()->vkBindVideoSessionMemoryKHR
		);

		m_Parameters.SetFunctor(
			GetContext().Get<IFunctions>()->vkCreateVideoSessionParametersKHR, 
			GetContext().Get<IFunctions>()->vkDestroyVideoSessionParametersKHR, 
			GetContext().Get<IFunctions>()->vkUpdateVideoSessionParametersKHR
		);

		CreateBuffer();
	}

	void VideoSession::CreateBuffer(VkDeviceSize size)
	{
		NEPTUNE_PROFILE_ZONE

		m_Buffer = CreateSP<DecodeBuffer>(GetContext());

		m_Buffer->CreateBuffer(size);
	}

	void VideoSession::CreateVideoSession(const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height, uint32_t slots)
	{
		NEPTUNE_PROFILE_ZONE

		auto property = GetContext().Get<IPhysicalDevice>()->QueryVideoSessionProperty(profile);
		m_DstFormat   = property.dstFormat;

		VkVideoSessionCreateFlagsKHR                sessionFlags{};
	    sessionFlags                             |= VK_VIDEO_SESSION_CREATE_INLINE_QUERIES_BIT_KHR;  // Enable if you use inline query pool

		static constexpr VkExtensionProperties h264DecodeStdVersion = { VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_EXTENSION_NAME, VK_STD_VULKAN_VIDEO_CODEC_H264_DECODE_SPEC_VERSION };
		static constexpr VkExtensionProperties h265DecodeStdVersion = { VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME, VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_VERSION };
		static constexpr VkExtensionProperties av1DecodeStdVersion  = { VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_EXTENSION_NAME , VK_STD_VULKAN_VIDEO_CODEC_AV1_DECODE_SPEC_VERSION  };
		static constexpr VkExtensionProperties vp9DecodeStdVersion  = { VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME , VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_VERSION  };
		static constexpr VkExtensionProperties h264EncodeStdVersion = { VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_EXTENSION_NAME, VK_STD_VULKAN_VIDEO_CODEC_H264_ENCODE_SPEC_VERSION };
		static constexpr VkExtensionProperties h265EncodeStdVersion = { VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_EXTENSION_NAME, VK_STD_VULKAN_VIDEO_CODEC_H265_ENCODE_SPEC_VERSION };
		static constexpr VkExtensionProperties av1EncodeStdVersion  = { VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_EXTENSION_NAME , VK_STD_VULKAN_VIDEO_CODEC_AV1_ENCODE_SPEC_VERSION  };

		VkVideoSessionCreateInfoKHR                 info{};
		info.sType                                = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR;
		info.flags                                = sessionFlags;
		info.pVideoProfile                        = &profile;
		info.queueFamilyIndex                     = GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().videoDecode.value();
		info.pictureFormat                        = m_DstFormat;
		info.maxCodedExtent                       = property.capabilities.maxCodedExtent;
		info.maxDpbSlots                          = slots;
		info.maxActiveReferencePictures           = slots;
		info.referencePictureFormat               = property.dpbFormat;
		info.pNext                                = nullptr;

		switch (profile.videoCodecOperation)
		{
			case VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR: info.pStdHeaderVersion = &h264DecodeStdVersion; break;
			case VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR: info.pStdHeaderVersion = &h265DecodeStdVersion; break;
			case VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR:  info.pStdHeaderVersion = &av1DecodeStdVersion ; break;
			case VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR:  info.pStdHeaderVersion = &vp9DecodeStdVersion ; break;
			case VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR: info.pStdHeaderVersion = &h264EncodeStdVersion; break;
			case VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR: info.pStdHeaderVersion = &h265EncodeStdVersion; break;
			case VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_BIT_KHR:  info.pStdHeaderVersion = &av1EncodeStdVersion ; break;
			default:
			{
				NEPTUNE_CORE_ERROR("Invalid VkVideoCodecOperationFlagBitsKHR in Calling CreateVideoSession()");
				return;
			}
		}

		m_Session.CreateVideoSession(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_Session, "VideoSession")

		uint32_t memoryRequirementsCount = 0;
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetVideoSessionMemoryRequirementsKHR(GetContext().Get<IDevice>()->Handle(), Handle(), &memoryRequirementsCount, NULL))

		std::vector<VkVideoSessionMemoryRequirementsKHR> memoryRequirements(memoryRequirementsCount, { VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR });
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetVideoSessionMemoryRequirementsKHR(GetContext().Get<IDevice>()->Handle(), Handle(), &memoryRequirementsCount, memoryRequirements.data()))

        std::vector<VkBindVideoSessionMemoryInfoKHR> sessionBindMemorys(memoryRequirementsCount, { VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR });

        for (uint32_t i = 0; i < memoryRequirementsCount; i++) 
        {
            uint32_t memoryTypeIndex = 0;
            uint32_t memoryTypeBits = memoryRequirements[i].memoryRequirements.memoryTypeBits;

            while(!(memoryTypeBits & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            {
                memoryTypeIndex++;
                memoryTypeBits >>= 1;
            }

            VkMemoryAllocateInfo                           memInfo{};
            memInfo.sType                                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            memInfo.allocationSize                       = memoryRequirements[i].memoryRequirements.size;
            memInfo.memoryTypeIndex                      = memoryTypeIndex;
            memInfo.pNext                                = nullptr;

            VkBindVideoSessionMemoryInfoKHR&               sessionBindMemory = sessionBindMemorys[i];
            sessionBindMemory.sType                      = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR;
            sessionBindMemory.memory                     = m_Session.AllocateMemory(memInfo);
            sessionBindMemory.memoryBindIndex            = memoryRequirements[i].memoryBindIndex;
            sessionBindMemory.memoryOffset               = 0;
            sessionBindMemory.memorySize                 = memoryRequirements[i].memoryRequirements.size;
            sessionBindMemory.pNext                      = nullptr;
        }

		m_Session.BindVideoSessionMemory(sessionBindMemorys);

		CreateQueryPool(profile, slots);

		CreateVideoSessionParameters(profile.videoCodecOperation);

		UpdateVideoSessionParameters();

		CreateDecodePictureBuffer(profile, width, height, slots, property.dpbFormat);

		CreateSamplerYcbcrConversion();
	}

	void VideoSession::CreateQueryPool(const VkVideoProfileInfoKHR& profile, uint32_t slot)
	{
		NEPTUNE_PROFILE_ZONE

		VkQueryPoolCreateInfo             info{};
		info.sType                      = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
		info.queryType                  = VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR;
		info.queryCount                 = slot;				        
		info.flags                      = 0;
		info.pNext                      = &profile;

		m_QueryPool = CreateSP<QueryPool>(GetContext());

		m_QueryPool->CreateQueryPool(info, AlignUp(sizeof(VkQueryResultStatusKHR), sizeof(uint64_t)));
	}

	void VideoSession::CreateVideoSessionParameters(VkVideoCodecOperationFlagsKHR op)
	{
		NEPTUNE_PROFILE_ZONE

		VkVideoDecodeH264SessionParametersCreateInfoKHR    decodeH264CreateInfo{};
		VkVideoDecodeH265SessionParametersCreateInfoKHR    decodeH265CreateInfo{};
		VkVideoDecodeAV1SessionParametersCreateInfoKHR     decodeAV1CreateInfo{};

		VkVideoSessionParametersCreateInfoKHR              createInfo{};
		createInfo.sType                                 = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
		createInfo.flags                                 = 0;
		createInfo.videoSessionParametersTemplate        = nullptr;
		createInfo.videoSession                          = Handle();

		switch (op)
		{
			case VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR:
			{
				decodeH264CreateInfo.sType                       = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR;
				decodeH264CreateInfo.maxStdSPSCount              = MaxStdSPSCount;
				decodeH264CreateInfo.maxStdPPSCount              = MaxStdPPSCount;
				decodeH264CreateInfo.pParametersAddInfo          = nullptr;
				decodeH264CreateInfo.pNext                       = nullptr;

				createInfo.pNext                                 = &decodeH264CreateInfo;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR:
			{
				decodeH265CreateInfo.sType                       = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
				decodeH265CreateInfo.maxStdVPSCount              = MaxStdVPSCount;
				decodeH265CreateInfo.maxStdSPSCount              = MaxStdSPSCount;
				decodeH265CreateInfo.maxStdPPSCount              = MaxStdPPSCount;
				decodeH265CreateInfo.pParametersAddInfo          = nullptr;
				decodeH265CreateInfo.pNext                       = nullptr;

				createInfo.pNext                                 = &decodeH265CreateInfo;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR:
			{
				decodeAV1CreateInfo.sType                        = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_SESSION_PARAMETERS_CREATE_INFO_KHR;
				decodeAV1CreateInfo.pStdSequenceHeader           = nullptr;
				decodeAV1CreateInfo.pNext                        = nullptr;

				createInfo.pNext                                 = &decodeAV1CreateInfo;
			}
			default:
			{
				NEPTUNE_CORE_ERROR("Invalid VideoOperation in Calling CreateVideoSessionParameters()");
				return;
			}
		}

		m_Parameters.CreateVideoSessionParameters(GetContext().Get<IDevice>()->Handle(), createInfo);

		DEBUGUTILS_SETOBJECTNAME(m_Parameters, "VideoSessionParameters")
	}

	void VideoSession::CreateDecodePictureBuffer(const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height, uint32_t slot, VkFormat format)
	{
		NEPTUNE_PROFILE_ZONE

		{
            VkVideoProfileListInfoKHR                          profileList{};
            profileList.sType                                = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
            profileList.pProfiles                            = &profile;
            profileList.profileCount                         = 1;

            VkImageCreateInfo                                  createInfo{};
		    createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		    createInfo.imageType                             = VK_IMAGE_TYPE_2D;
		    createInfo.extent.width                          = width;
		    createInfo.extent.height                         = height;
		    createInfo.extent.depth                          = 1;
		    createInfo.mipLevels                             = 1;
		    createInfo.arrayLayers                           = 1;
		    createInfo.format                                = format;
		    createInfo.tiling                                = VK_IMAGE_TILING_OPTIMAL;
		    createInfo.initialLayout                         = VK_IMAGE_LAYOUT_UNDEFINED;
		    createInfo.usage                                 = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR |
														       VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR |
                                                               VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		    createInfo.sharingMode                           = VK_SHARING_MODE_EXCLUSIVE;
		    createInfo.samples                               = VK_SAMPLE_COUNT_1_BIT;
		    createInfo.flags                                 = 0;
            createInfo.pNext                                 = &profileList;

			m_DPB.CreateImage(createInfo, slot);

			m_DPB.TransitionLayout(VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
        }

        {
            VkImageViewUsageCreateInfo                         viewUsage{};
            viewUsage.sType                                  = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
            viewUsage.usage                                  = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR |
                                                               VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR;

            VkImageViewCreateInfo                              createInfo{};
		    createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.flags                                 = 0;

		    createInfo.viewType                              = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
		    createInfo.format                                = format;

		    createInfo.components.r                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.g                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.b                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.a                          = VK_COMPONENT_SWIZZLE_IDENTITY;
												       	  
		    createInfo.subresourceRange.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
		    createInfo.subresourceRange.baseMipLevel         = 0;
		    createInfo.subresourceRange.levelCount           = 1;
		    createInfo.subresourceRange.baseArrayLayer       = 0;
		    createInfo.subresourceRange.layerCount           = 1;
            createInfo.pNext                                 = &viewUsage;

			for (int i = 0; i < slot; i++)
			{
				createInfo.image                             = m_DPB.Handle(i);

				m_DPB.CreateImageView(createInfo, i);
			}
        }
	}

	void VideoSession::CreateSamplerYcbcrConversion()
	{
		NEPTUNE_PROFILE_ZONE

		VkSamplerYcbcrConversionCreateInfo                     info{};
		info.sType                                           = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
		info.format                                          = m_DstFormat;
		info.ycbcrModel                                      = VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709;
		info.ycbcrRange                                      = VK_SAMPLER_YCBCR_RANGE_ITU_NARROW;
		info.components.r                                    = VK_COMPONENT_SWIZZLE_R;
		info.components.g                                    = VK_COMPONENT_SWIZZLE_G;
		info.components.b                                    = VK_COMPONENT_SWIZZLE_B;
		info.components.a                                    = VK_COMPONENT_SWIZZLE_A;
		info.xChromaOffset                                   = VK_CHROMA_LOCATION_COSITED_EVEN;
		info.yChromaOffset                                   = VK_CHROMA_LOCATION_COSITED_EVEN;
		info.chromaFilter                                    = VK_FILTER_LINEAR;
		info.forceExplicitReconstruction                     = VK_FALSE;

		m_Conversion.CreateSamplerYcbcrConversion(GetContext().Get<IDevice>()->Handle(), info);
	}

	void VideoSession::CreateDecodeRenderTarget(RenderTarget* rt, const VkVideoProfileInfoKHR& profile, uint32_t width, uint32_t height) const
	{
		NEPTUNE_PROFILE_ZONE

		auto image = CreateSP<Image>(GetContext());

		VkSamplerYcbcrConversionInfo                           conversionInfo{};
		conversionInfo.sType                                 = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
		conversionInfo.conversion                            = m_Conversion.GetHandle();
		conversionInfo.pNext                                 = nullptr;

		{
			VkOpticalFlowImageFormatInfoNV                     opticalFormatInfo{};
			opticalFormatInfo.sType                          = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
			opticalFormatInfo.usage                          = VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV;
			opticalFormatInfo.pNext                          = nullptr;

            VkVideoProfileListInfoKHR                          profileList{};
            profileList.sType                                = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
            profileList.pProfiles                            = &profile;
            profileList.profileCount                         = 1;
			profileList.pNext                                = nullptr;//&opticalFormatInfo;

            VkImageCreateInfo                                  createInfo{};
		    createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		    createInfo.imageType                             = VK_IMAGE_TYPE_2D;
		    createInfo.extent.width                          = width;
		    createInfo.extent.height                         = height;
		    createInfo.extent.depth                          = 1;
		    createInfo.mipLevels                             = 1;
		    createInfo.arrayLayers                           = 1;
		    createInfo.format                                = m_DstFormat;
		    createInfo.tiling                                = VK_IMAGE_TILING_OPTIMAL;
		    createInfo.initialLayout                         = VK_IMAGE_LAYOUT_UNDEFINED;
		    createInfo.usage                                 = VK_IMAGE_USAGE_SAMPLED_BIT |
															   VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
														       VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		    createInfo.sharingMode                           = VK_SHARING_MODE_EXCLUSIVE;
		    createInfo.samples                               = VK_SAMPLE_COUNT_1_BIT;
		    createInfo.flags                                 = 0;
            createInfo.pNext                                 = &profileList;

			image->CreateImage(createInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			image->TransitionLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        }

        {     
            VkImageViewUsageCreateInfo                         viewUsage{};
            viewUsage.sType                                  = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
            viewUsage.usage                                  = VK_IMAGE_USAGE_SAMPLED_BIT |
                                                               VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			viewUsage.pNext                                  = &conversionInfo;

            VkImageViewCreateInfo                              createInfo{};
		    createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.flags                                 = 0;
            createInfo.image                                 = image->Handle();

		    createInfo.viewType                              = VK_IMAGE_VIEW_TYPE_2D;
		    createInfo.format                                = m_DstFormat;

		    createInfo.components.r                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.g                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.b                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.a                          = VK_COMPONENT_SWIZZLE_IDENTITY;
												       	  
		    createInfo.subresourceRange.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
		    createInfo.subresourceRange.baseMipLevel         = 0;
		    createInfo.subresourceRange.levelCount           = 1;
		    createInfo.subresourceRange.baseArrayLayer       = 0;
		    createInfo.subresourceRange.layerCount           = 1;
            createInfo.pNext                                 = &viewUsage;

			image->CreateImageView(createInfo);
        }

		{
			VkSamplerCreateInfo                                createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			createInfo.magFilter                             = VK_FILTER_LINEAR;
			createInfo.minFilter                             = VK_FILTER_LINEAR;
			createInfo.addressModeU                          = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			createInfo.addressModeV                          = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			createInfo.addressModeW                          = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			createInfo.anisotropyEnable                      = VK_FALSE;
			createInfo.pNext                                 = &conversionInfo;

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

			image->CreateSampler(createInfo);
		}

		image->SetName("DecodeRenderTarget");

		rt->SetImage(image);
	}

	void VideoSession::CreateFlowVectorRenderTarget(class RenderTarget* rt, uint32_t width, uint32_t height) const
	{
		NEPTUNE_PROFILE_ZONE

		auto image = CreateSP<Image>(GetContext());

		{
			VkOpticalFlowImageFormatInfoNV                     opticalFormatInfo{};
			opticalFormatInfo.sType                          = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
			opticalFormatInfo.usage                          = VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV;

            VkImageCreateInfo                                  createInfo{};
		    createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		    createInfo.imageType                             = VK_IMAGE_TYPE_2D;
		    createInfo.extent.width                          = width;
		    createInfo.extent.height                         = height;
		    createInfo.extent.depth                          = 1;
		    createInfo.mipLevels                             = 1;
		    createInfo.arrayLayers                           = 1;
		    createInfo.format                                = VK_FORMAT_R16G16_SFIXED5_NV;
		    createInfo.tiling                                = VK_IMAGE_TILING_OPTIMAL;
		    createInfo.initialLayout                         = VK_IMAGE_LAYOUT_UNDEFINED;
		    createInfo.usage                                 = VK_IMAGE_USAGE_STORAGE_BIT | 
															   VK_IMAGE_USAGE_SAMPLED_BIT;
		    createInfo.sharingMode                           = VK_SHARING_MODE_EXCLUSIVE;
		    createInfo.samples                               = VK_SAMPLE_COUNT_1_BIT;
		    createInfo.flags                                 = 0;
			createInfo.pNext                                 = nullptr;//&opticalFormatInfo;

			image->CreateImage(createInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			image->TransitionLayout(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        }

        {
            VkImageViewCreateInfo                              createInfo{};
		    createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.flags                                 = 0;
            createInfo.image                                 = image->Handle();

		    createInfo.viewType                              = VK_IMAGE_VIEW_TYPE_2D;
		    createInfo.format                                = VK_FORMAT_R16G16_SFIXED5_NV;

		    createInfo.components.r                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.g                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.b                          = VK_COMPONENT_SWIZZLE_IDENTITY;
		    createInfo.components.a                          = VK_COMPONENT_SWIZZLE_IDENTITY;
												       	  
		    createInfo.subresourceRange.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
		    createInfo.subresourceRange.baseMipLevel         = 0;
		    createInfo.subresourceRange.levelCount           = 1;
		    createInfo.subresourceRange.baseArrayLayer       = 0;
		    createInfo.subresourceRange.layerCount           = 1;

			image->CreateImageView(createInfo);
        }

		{
			VkSamplerCreateInfo                                createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			createInfo.magFilter                             = VK_FILTER_NEAREST;
			createInfo.minFilter                             = VK_FILTER_NEAREST;
			createInfo.addressModeU                          = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			createInfo.addressModeV                          = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			createInfo.addressModeW                          = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			createInfo.anisotropyEnable                      = VK_FALSE;

			VkPhysicalDeviceProperties                         properties{};
			vkGetPhysicalDeviceProperties(GetContext().Get<IPhysicalDevice>()->Handle(), &properties);

			createInfo.maxAnisotropy                         = properties.limits.maxSamplerAnisotropy;
			createInfo.borderColor                           = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			createInfo.unnormalizedCoordinates               = VK_FALSE;
			createInfo.compareEnable                         = VK_FALSE;
			createInfo.compareOp                             = VK_COMPARE_OP_ALWAYS;
													         
			createInfo.mipmapMode                            = VK_SAMPLER_MIPMAP_MODE_NEAREST;
			createInfo.mipLodBias                            = 0.0f;
			createInfo.minLod                                = 0;
			createInfo.maxLod                                = 1;

			image->CreateSampler(createInfo);
		}

		image->SetName("VectorFlowRenderTarget");

		rt->SetImage(image);
	}

	void VideoSession::AddVideoSessionParameters(const SP<StdVideoPictureParametersSet>& param)
	{
		NEPTUNE_PROFILE_ZONE

		uint8_t set = 0;

		switch (param->GetStdType())
		{
			case StdVideoPictureParametersSet::StdType::TYPE_H264_SPS: set = param->GetStdH264Sps()->seq_parameter_set_id;       break;
			case StdVideoPictureParametersSet::StdType::TYPE_H264_PPS: set = param->GetStdH264Pps()->pic_parameter_set_id;       break;
			case StdVideoPictureParametersSet::StdType::TYPE_H265_VPS: set = param->GetStdH265Vps()->vps_video_parameter_set_id; break;
			case StdVideoPictureParametersSet::StdType::TYPE_H265_SPS: set = param->GetStdH265Sps()->sps_seq_parameter_set_id;   break;
			case StdVideoPictureParametersSet::StdType::TYPE_H265_PPS: set = param->GetStdH265Pps()->pps_seq_parameter_set_id;   break;
			default:
			{
				NEPTUNE_CORE_ERROR("Invalid StdType in Calling UpdateVideoSessionParameters()")
				return;
			}
		}

		m_ParameterSets[param->GetParameterType()][set] = param;
	}

	bool VideoSession::GetDecodeResult() const
	{
		NEPTUNE_PROFILE_ZONE

		auto result = m_QueryPool->GetQueryPoolResult(m_DPB.DecodeSlot());
		
		return result == VK_QUERY_RESULT_STATUS_COMPLETE_KHR;
	}

	void VideoSession::PushDisplaySlot(uint8_t slot)
	{
		NEPTUNE_PROFILE_ZONE

		m_DisplaySlots.push(slot);
	}

	uint8_t VideoSession::PopDisplaySlot()
	{
		NEPTUNE_PROFILE_ZONE

		auto slot = m_DisplaySlots.front();

		m_DisplaySlots.pop();

		return slot;
	}

	void VideoSession::UpdateVideoSessionParameters()
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t count = 0;

		for (auto& paramSets : m_ParameterSets | std::ranges::views::values)
		{
			for (auto& param : paramSets | std::ranges::views::values)
			{
				VkVideoDecodeH264SessionParametersAddInfoKHR	   decodeH264AddInfo{};
				VkVideoDecodeH265SessionParametersAddInfoKHR       decodeH265AddInfo{};
		
				VkVideoSessionParametersUpdateInfoKHR              updateInfo {};
				updateInfo.sType                                 = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR;
				updateInfo.updateSequenceCount                   = ++count;

				switch (param->GetStdType())
				{
					case StdVideoPictureParametersSet::StdType::TYPE_H264_SPS:
					{
						decodeH264AddInfo.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
						decodeH264AddInfo.stdSPSCount            = 1;
						decodeH264AddInfo.pStdSPSs               = param->GetStdH264Sps();

						updateInfo.pNext = &decodeH264AddInfo;
						break;
					}
					case StdVideoPictureParametersSet::StdType::TYPE_H264_PPS:
					{
						decodeH264AddInfo.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
						decodeH264AddInfo.stdPPSCount            = 1;
						decodeH264AddInfo.pStdPPSs               = param->GetStdH264Pps();

						updateInfo.pNext                         = &decodeH264AddInfo;
						break;
					}
					case StdVideoPictureParametersSet::StdType::TYPE_H265_VPS:
					{
						decodeH265AddInfo.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
						decodeH265AddInfo.stdVPSCount            = 1;
						decodeH265AddInfo.pStdVPSs               = param->GetStdH265Vps();

						updateInfo.pNext                         = &decodeH265AddInfo;
						break;
					}
					case StdVideoPictureParametersSet::StdType::TYPE_H265_SPS:
					{
						decodeH265AddInfo.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
						decodeH265AddInfo.stdSPSCount            = 1;
						decodeH265AddInfo.pStdSPSs               = param->GetStdH265Sps();

						updateInfo.pNext                         = &decodeH265AddInfo;
						break;
					}
					case StdVideoPictureParametersSet::StdType::TYPE_H265_PPS:
					{
						decodeH265AddInfo.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;
						decodeH265AddInfo.stdPPSCount            = 1;
						decodeH265AddInfo.pStdPPSs               = param->GetStdH265Pps();

						updateInfo.pNext                         = &decodeH265AddInfo;
						break;
					}
					default:
					{
						NEPTUNE_CORE_ERROR("Invalid StdType in Calling UpdateVideoSessionParameters()")
						return;
					}
				}

				m_Parameters.UpdateVideoSessionParameters(GetContext().Get<IDevice>()->Handle(), updateInfo);
			}
		}

		m_ParameterSets.clear();
	}
}

#endif