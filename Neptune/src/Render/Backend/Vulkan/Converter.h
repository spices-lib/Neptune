/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Mesh/Mesh.h"
#include "Resource/Shader/Shader.h"

#include <vma/vk_mem_alloc.h>

namespace Neptune::Vulkan {

	/**
	* @brief Convert TextureFormat to VkFormat.
	* 
	* @param[in] f TextureFormat.
	* 
	* @return Returns VkFormat.
	*/
	VkFormat ToVkFormat(TextureFormat f);

	/**
	* @brief Convert TextureDomain to VkImageType.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns VkImageType.
	*/
	VkImageType ToVkImageType(TextureDomain d);

	/**
	* @brief Convert TextureDomain to VkImageViewType.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns TextureDomain.
	*/
	VkImageViewType ToVkImageViewType(TextureDomain d);

	/**
	* @brief Convert RHIMemoryUsage to VkMemoryPropertyFlags.
	*
	* @param[in] u RHIMemoryUsage.
	*
	* @return Returns VkMemoryPropertyFlags.
	*/
	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(RHIMemoryUsage u);

	/**
	* @brief Convert RHIMemoryUsage to VmaMemoryUsage.
	*
	* @param[in] u RHIMemoryUsage.
	*
	* @return Returns VmaMemoryUsage.
	*/
	VmaMemoryUsage ToVmaMemoryUsage(RHIMemoryUsage u);

	/**
	* @brief Convert CullMode to VkCullModeFlags.
	*
	* @param[in] c CullMode.
	*
	* @return Returns VkCullModeFlags.
	*/
	VkCullModeFlags ToVkCullModeFlags(CullMode c);

	/**
	* @brief Convert ShaderStage to VkShaderStageFlagBits.
	*
	* @param[in] s ShaderStage.
	*
	* @return Returns VkShaderStageFlagBits.
	*/
	VkShaderStageFlagBits ToVkShaderStageFlagBits(ShaderStage s);

	/**
	* @brief Convert AttachmentOP to VkAttachmentLoadOp.
	*
	* @param[in] op AttachmentOP.
	*
	* @return Returns VkAttachmentLoadOp.
	*/
	VkAttachmentLoadOp ToVkAttachmentLoadOp(AttachmentOP op);

	/**
	* @brief Convert AttachmentLayout to VkImageLayout.
	*
	* @param[in] l AttachmentLayout.
	*
	* @return Returns VkImageLayout.
	*/
	VkImageLayout ToVkImageLayout(AttachmentLayout l);

	/**
	* @brief Convert VkFormat to TextureFormat.
	*
	* @param[in] f VkFormat.
	*
	* @return Returns TextureFormat.
	*/
	TextureFormat ToTextureFormat(VkFormat f);

	/**
	* @brief Convert VkMemoryHeapFlags to std::string.
	*
	* @param[in] flag VkMemoryHeapFlags.
	*
	* @return Returns std::string.
	*/
	std::string ToString(VkMemoryHeapFlags flag);

}