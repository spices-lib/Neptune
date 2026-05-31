/**
* @file FrameBuffer.h.
* @brief The FrameBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::FrameBuffer Class.
	* This class defines the Vulkan::Unit::FrameBuffer behaves.
	*/
	class FrameBuffer : public Unit<VkFramebuffer, VkObjectType::VK_OBJECT_TYPE_FRAMEBUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		FrameBuffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~FrameBuffer() override;

		/**
		* @brief Create FrameBuffer.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkFramebufferCreateInfo.
		*/
		void CreateFrameBuffer(VkDevice device, const VkFramebufferCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;          // @brief VkDevice
	};
}

#endif