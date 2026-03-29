/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "DebugUtilsObject.h"
#include "Functions.h"
#include "Device.h"

namespace Neptune::Vulkan {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT             labelInfo{};
		labelInfo.sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName           = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkCmdBeginDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::EndLabel(VkCommandBuffer cmdBuffer) const
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Get<IFunctions>()->vkCmdEndDebugUtilsLabelEXT(cmdBuffer);
	}

	void DebugUtilsObject::InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT         labelInfo{};
		labelInfo.sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName       = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkCmdInsertDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::BeginQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkQueueBeginDebugUtilsLabelEXT(queue, &labelInfo);
	}

	void DebugUtilsObject::EndQueueLabel(VkQueue queue) const
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Get<IFunctions>()->vkQueueEndDebugUtilsLabelEXT(queue);
	}

	void DebugUtilsObject::InsertQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color) const
	{
		NEPTUNE_PROFILE_ZONE

		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkQueueInsertDebugUtilsLabelEXT(queue, &labelInfo);
	}
}