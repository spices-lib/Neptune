/**
* @file VideoSessionParameters.h.
* @brief The VideoSessionParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

#include <vector>

namespace Neptune::Vulkan::Unit {

	constexpr uint32_t MAX_BOUND_MEMORY = 16;

	/**
	* @brief Vulkan::Unit::VideoSession Class.
	* This class defines the Vulkan::Unit::VideoSession behaves.
	*/
	class VideoSession : public Common::Unit<VkVideoSessionKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		VideoSession() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~VideoSession() override;

		/**
		* @brief Set Functor.
		* 
		* @param[in] create PFN_vkCreateVideoSessionKHR.
		* @param[in] destroy PFN_vkDestroyVideoSessionKHR.
		* @param[in] bind PFN_vkBindVideoSessionMemoryKHR.
		*/
		void SetFunctor(PFN_vkCreateVideoSessionKHR create, PFN_vkDestroyVideoSessionKHR destroy, PFN_vkBindVideoSessionMemoryKHR bind);

		/**
		* @brief Create VideoSession.
		*
		* @param[in] device VkDevice.
		* @param[in] createInfo VkVideoSessionCreateInfoKHR.
		*/
		void CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo);

		/**
		* @brief Allocate Memory.
		*
		* @param[in] info VkMemoryAllocateInfo.
		* 
		* @return Returns VkDeviceMemory.
		*/
		VkDeviceMemory AllocateMemory(const VkMemoryAllocateInfo& info);

		/**
		* @brief Bind VideoSession Memory.
		*
		* @param[in] infos VkBindVideoSessionMemoryInfoKHR.
		*/
		void BindVideoSessionMemory(const std::vector<VkBindVideoSessionMemoryInfoKHR>& infos) const;

	private:

		VkDevice                              m_Device = VK_NULL_HANDLE;                        // @brief VkDevice.
		std::vector<VkDeviceMemory>           m_Memories{};                                     // @brief VkDeviceMemory.
		PFN_vkCreateVideoSessionKHR           vkCreateVideoSessionKHR = VK_NULL_HANDLE;         // @brief PFN_vkCreateVideoSessionKHR.
		PFN_vkDestroyVideoSessionKHR          vkDestroyVideoSessionKHR = VK_NULL_HANDLE;        // @brief PFN_vkDestroyVideoSessionKHR.
		PFN_vkBindVideoSessionMemoryKHR       vkBindVideoSessionMemoryKHR = VK_NULL_HANDLE;     // @brief PFN_vkBindVideoSessionMemoryKHR.
	};
}

#endif