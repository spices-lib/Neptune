/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Converter.h"

namespace Neptune::Vulkan {

	VkFormat ToVkFormat(TextureFormat f)
	{
		NEPTUNE_PROFILE_ZONE

		switch (f)
		{
			case TextureFormat::RGBA8_UNORM:               return VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
			case TextureFormat::RGBA16_SFLOAT:             return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;
			case TextureFormat::R8_G8B8_2PLANE_420_UNORM:  return VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported Texture Format To VkFormat.")
				return VK_FORMAT_R8G8B8A8_UNORM;
			}
		}
	}

	VkImageType ToVkImageType(TextureDomain d)
	{
		NEPTUNE_PROFILE_ZONE

		switch (d)
		{
			case TextureDomain::Texture1D:      return VkImageType::VK_IMAGE_TYPE_1D;
			case TextureDomain::Texture1DArray: return VkImageType::VK_IMAGE_TYPE_1D;
			case TextureDomain::Texture2D:      return VkImageType::VK_IMAGE_TYPE_2D;
			case TextureDomain::Texture2DArray: return VkImageType::VK_IMAGE_TYPE_2D;
			case TextureDomain::Texture3D:      return VkImageType::VK_IMAGE_TYPE_3D;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported Texture Domain To VkImageType.")
				return VK_IMAGE_TYPE_1D;
			}
		}
	}

	VkImageViewType ToVkImageViewType(TextureDomain d)
	{
		NEPTUNE_PROFILE_ZONE

		switch (d)
		{
			case TextureDomain::Texture1D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D;
			case TextureDomain::Texture1DArray: return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D_ARRAY;
			case TextureDomain::Texture2D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
			case TextureDomain::Texture2DArray: return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D_ARRAY;
			case TextureDomain::Texture3D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_3D;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported Texture Domain To VkImageViewType.")
				return VK_IMAGE_VIEW_TYPE_2D;
			}
		}
	}

	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(RHIMemoryUsage u)
	{
		NEPTUNE_PROFILE_ZONE

		switch (u)
		{
			case RHIMemoryUsage::Device:    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			case RHIMemoryUsage::Host:      return VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			case RHIMemoryUsage::Shared:    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			case RHIMemoryUsage::Preserved: return VK_MEMORY_PROPERTY_PROTECTED_BIT;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported RHIMemoryUsage To VkMemoryPropertyFlags.")
				return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			}
		}
	}

	VmaMemoryUsage ToVmaMemoryUsage(RHIMemoryUsage u)
	{
		NEPTUNE_PROFILE_ZONE

		switch (u)
		{
			case RHIMemoryUsage::Device:    return VMA_MEMORY_USAGE_GPU_ONLY;
			case RHIMemoryUsage::Host:      return VMA_MEMORY_USAGE_CPU_ONLY;
			case RHIMemoryUsage::Shared:    return VMA_MEMORY_USAGE_CPU_TO_GPU;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported RHIMemoryUsage To VmaMemoryUsage.")
				return VMA_MEMORY_USAGE_GPU_ONLY;
			}
		}
	}

	VkCullModeFlags ToVkCullModeFlags(CullMode c)
	{
		NEPTUNE_PROFILE_ZONE

		switch (c)
		{
			case CullMode::None:    return VK_CULL_MODE_NONE;
			case CullMode::Front:   return VK_CULL_MODE_FRONT_BIT;
			case CullMode::Back:    return VK_CULL_MODE_BACK_BIT;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported CullMode To VkCullModeFlags.")
				return VK_CULL_MODE_NONE;
			}
		}
	}

	VkShaderStageFlagBits ToVkShaderStageFlagBits(ShaderStage s)
	{
		NEPTUNE_PROFILE_ZONE

		switch (s)
		{
			case ShaderStage::Vertex:    return VK_SHADER_STAGE_VERTEX_BIT;
			case ShaderStage::Fragment:  return VK_SHADER_STAGE_FRAGMENT_BIT;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported ShaderStage To VkShaderStageFlagBits.")
				return VK_SHADER_STAGE_VERTEX_BIT;
			}
		}
	}

	VkAttachmentLoadOp ToVkAttachmentLoadOp(AttachmentOP op)
	{
		NEPTUNE_PROFILE_ZONE

		switch (op)
		{
			case AttachmentOP::Clear:    return VK_ATTACHMENT_LOAD_OP_CLEAR;
			case AttachmentOP::Load:     return VK_ATTACHMENT_LOAD_OP_LOAD;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported AttachmentOP To VkAttachmentLoadOp.")
				return VK_ATTACHMENT_LOAD_OP_CLEAR;
			}
		}
	}

	VkImageLayout ToVkImageLayout(AttachmentLayout l)
	{
		NEPTUNE_PROFILE_ZONE

		switch (l)
		{
			case AttachmentLayout::Undefined:           return VK_IMAGE_LAYOUT_UNDEFINED;
			case AttachmentLayout::ColorAttachment:     return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			case AttachmentLayout::ShaderRead:          return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported AttachmentLayout To VkImageLayout.")
				return VK_IMAGE_LAYOUT_UNDEFINED;
			}
		}
	}

	TextureFormat ToTextureFormat(VkFormat f)
	{
		NEPTUNE_PROFILE_ZONE

		switch (f)
		{
			case VkFormat::VK_FORMAT_R8G8B8A8_UNORM:                  return TextureFormat::RGBA8_UNORM;
			case VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT:             return TextureFormat::RGBA16_SFLOAT;
			case VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM:        return TextureFormat::R8_G8B8_2PLANE_420_UNORM;
			default:
			{
				NEPTUNE_CORE_WARN("Unsupported VkFormat To Texture Format.")
				return TextureFormat::RGBA8_UNORM;
			}
		}
	}

	std::string ToString(VkMemoryHeapFlags flag)
	{
		NEPTUNE_PROFILE_ZONE

		switch (flag)
		{
		case VK_MEMORY_HEAP_DEVICE_LOCAL_BIT:
			return "Device Local";
		case VK_MEMORY_HEAP_MULTI_INSTANCE_BIT:        // NOTICE THAT: enum value also represents "VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR"
			return "Multiple Instance";
		default:
			// In case that it does NOT correspond to device local memory
			return "Host Local";
		}
	}
}

#endif