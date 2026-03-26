#pragma once
#include "Core.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Mesh/Mesh.h"
#include "Resource/Shader/Shader.h"
#include <vma/vk_mem_alloc.h>

namespace Neptune::Vulkan {

	VkFormat ToVkFormat(TextureFormat f);

	VkImageType ToVkImageType(TextureDomain d);

	VkImageViewType ToVkImageViewType(TextureDomain d);

	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(RHIMemoryUsage u);

	VmaMemoryUsage ToVmaMemoryUsage(RHIMemoryUsage u);

	VkCullModeFlags ToVkCullModeFlags(CullMode c);

	VkShaderStageFlagBits ToVkShaderStageFlagBits(ShaderStage s);

	VkAttachmentLoadOp ToVkAttachmentLoadOp(AttachmentOP op);

	VkImageLayout ToVkImageLayout(AttachmentLayout l);

	TextureFormat ToTextureFormat(VkFormat f);

	std::string ToString(VkMemoryHeapFlags flag);
}