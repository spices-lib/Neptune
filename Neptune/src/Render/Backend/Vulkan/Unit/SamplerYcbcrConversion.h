/**
* @file SamplerYcbcrConversion.h.
* @brief The SamplerYcbcrConversion Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::SamplerYcbcrConversion Class.
	* This class defines the Vulkan::Unit::SamplerYcbcrConversion behaves.
	*/
	class SamplerYcbcrConversion : public Unit<VkSamplerYcbcrConversion, VkObjectType::VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		SamplerYcbcrConversion() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~SamplerYcbcrConversion() override;

		/**
		* @brief Create SamplerYcbcrConversion.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkSamplerYcbcrConversionCreateInfo.
		*/
		void CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
	};
}