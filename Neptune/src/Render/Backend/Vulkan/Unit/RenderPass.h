/**
* @file RenderPass.h.
* @brief The RenderPass Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::RenderPass Class.
	* This class defines the Vulkan::Unit::RenderPass behaves.
	*/
	class RenderPass : public Common::Unit<VkRenderPass, VkObjectType::VK_OBJECT_TYPE_RENDER_PASS>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RenderPass() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~RenderPass() override;

		/**
		* @brief Create RenderPass.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkRenderPassCreateInfo.
		*/
		void CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;    // @brief VkDevice.
	};
}

#endif