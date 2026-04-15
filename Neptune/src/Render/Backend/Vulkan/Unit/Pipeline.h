/**
* @file Pipeline.h.
* @brief The Pipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Pipeline Class.
	* This class defines the Vulkan::Unit::Pipeline behaves.
	*/
	class Pipeline : public Unit<VkPipeline, VkObjectType::VK_OBJECT_TYPE_PIPELINE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Pipeline() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Pipeline() override;

		/**
		* @brief Create GraphicPipeline.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkGraphicsPipelineCreateInfo.
		*/
		void CreateGraphicPipeline(VkDevice device, const VkGraphicsPipelineCreateInfo& info);

		/**
		* @brief Create ComputePipeline.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkComputePipelineCreateInfo.
		*/
		void CreateComputePipeline(VkDevice device, const VkComputePipelineCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;        // @brief VkDevice.
	};
}

#endif