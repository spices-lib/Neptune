/**
* @file PipelineLayout.h.
* @brief The PipelineLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::PipelineLayout Class.
	* This class defines the Vulkan::Unit::PipelineLayout behaves.
	*/
	class PipelineLayout : public Common::Unit<VkPipelineLayout, VkObjectType::VK_OBJECT_TYPE_PIPELINE_LAYOUT>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		PipelineLayout() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~PipelineLayout() override;

		/**
		* @brief Create PipelineLayout.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkPipelineLayoutCreateInfo.
		*/
		void CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;        // @brief VkDevice.
	};
}

#endif