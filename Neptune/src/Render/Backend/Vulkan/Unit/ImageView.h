/**
* @file ImageView.h.
* @brief The ImageView Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::ImageView Class.
	* This class defines the Vulkan::Unit::ImageView behaves.
	*/
	class ImageView : public Common::Unit<VkImageView, VkObjectType::VK_OBJECT_TYPE_IMAGE_VIEW>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		ImageView() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~ImageView() override;

		/**
		* @brief Create Image View.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkImageViewCreateInfo.
		*/
		void CreateImageView(VkDevice device, const VkImageViewCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice
	};
}

#endif