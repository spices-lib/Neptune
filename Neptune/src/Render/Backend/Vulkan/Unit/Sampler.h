/**
* @file Sampler.h.
* @brief The Sampler Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Sampler Class.
	* This class defines the Vulkan::Unit::Sampler behaves.
	*/
	class Sampler : public Common::Unit<VkSampler, VkObjectType::VK_OBJECT_TYPE_SAMPLER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Sampler() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Sampler() override;

		/**
		* @brief Create Sampler.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkSamplerCreateInfo.
		*/
		void CreateSampler(VkDevice device, const VkSamplerCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;   // @brief VkDevice.
	};
}

#endif