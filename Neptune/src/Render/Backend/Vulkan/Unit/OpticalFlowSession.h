/**
* @file OpticalFlowSession.h.
* @brief The OpticalFlowSession Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::OpticalFlowSession Class.
	* This class defines the Vulkan::Unit::OpticalFlowSession behaves.
	*/
	class OpticalFlowSession : public Unit<VkOpticalFlowSessionNV, VkObjectType::VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		OpticalFlowSession() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~OpticalFlowSession() override;

		/**
		* @brief Set Functor.
		* 
		* @param[in] create PFN_vkCreateOpticalFlowSessionNV.
		* @param[in] destroy PFN_vkDestroyOpticalFlowSessionNV.
		* @param[in] bind PFN_vkBindOpticalFlowSessionImageNV.
		*/
		void SetFunctor(PFN_vkCreateOpticalFlowSessionNV create, PFN_vkDestroyOpticalFlowSessionNV destroy, PFN_vkBindOpticalFlowSessionImageNV bind);

		/**
		* @brief Create OpticalFlowSession.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkOpticalFlowSessionCreateInfoNV.
		*/
		void CreateOpticalFlowSession(VkDevice device, const VkOpticalFlowSessionCreateInfoNV& info);

		/**
		* @brief Bind OpticalFlowSessionImage.
		*
		* @param[in] bindPoint VkOpticalFlowSessionBindingPointNV.
		* @param[in] view VkImageView.
		* @param[in] layout VkImageLayout.
		*/
		void BindOpticalFlowSessionImage(VkOpticalFlowSessionBindingPointNV bindPoint, VkImageView view, VkImageLayout layout) const;

	private:

		VkDevice                            m_Device = VK_NULL_HANDLE;            // @brief VkDevice
		PFN_vkCreateOpticalFlowSessionNV    vkCreateOpticalFlowSessionNV;         // @brief PFN_vkCreateOpticalFlowSessionNV
		PFN_vkDestroyOpticalFlowSessionNV   vkDestroyOpticalFlowSessionNV;        // @brief PFN_vkDestroyOpticalFlowSessionNV
		PFN_vkBindOpticalFlowSessionImageNV vkBindOpticalFlowSessionImageNV;      // @brief PFN_vkBindOpticalFlowSessionImageNV

	};
}