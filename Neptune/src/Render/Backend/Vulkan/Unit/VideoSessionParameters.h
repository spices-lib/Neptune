/**
* @file VideoSessionParameters.h.
* @brief The VideoSessionParameters Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::VideoSessionParameters Class.
	* This class defines the Vulkan::Unit::VideoSessionParameters behaves.
	*/
	class VideoSessionParameters : public Unit<VkVideoSessionParametersKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		VideoSessionParameters() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~VideoSessionParameters() override;

		/**
		* @brief Set Functor.
		*
		* @param[in] create PFN_vkCreateVideoSessionParametersKHR.
		* @param[in] destroy PFN_vkDestroyVideoSessionParametersKHR.
		* @param[in] update PFN_vkUpdateVideoSessionParametersKHR.
		*/
		void SetFunctor(PFN_vkCreateVideoSessionParametersKHR create, PFN_vkDestroyVideoSessionParametersKHR destroy, PFN_vkUpdateVideoSessionParametersKHR update);

		/**
		* @brief Create VideoSessionParameters.
		*
		* @param[in] device VkDevice.
		* @param[in] createInfo VkVideoSessionParametersCreateInfoKHR.
		*/
		void CreateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersCreateInfoKHR& createInfo);

		/**
		* @brief Update VideoSessionParameters.
		*
		* @param[in] device VkDevice.
		* @param[in] updateInfo VkVideoSessionParametersUpdateInfoKHR.
		*/
		void UpdateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersUpdateInfoKHR& updateInfo) const;

	private:

		VkDevice                               m_Device = VK_NULL_HANDLE;                                 // @brief VkDevice.
		PFN_vkCreateVideoSessionParametersKHR  vkCreateVideoSessionParametersKHR = VK_NULL_HANDLE;        // @brief PFN_vkCreateVideoSessionParametersKHR.
		PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR = VK_NULL_HANDLE;       // @brief PFN_vkDestroyVideoSessionParametersKHR.
		PFN_vkUpdateVideoSessionParametersKHR  vkUpdateVideoSessionParametersKHR = VK_NULL_HANDLE;        // @brief PFN_vkUpdateVideoSessionParametersKHR.
	};
}

#endif