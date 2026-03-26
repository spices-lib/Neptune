#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	class SamplerYcbcrConversion : public Unit<VkSamplerYcbcrConversion, VkObjectType::VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION>
	{
	public:

		using Handle = Unit::Handle;

	public:

		SamplerYcbcrConversion() : Unit() {}

		~SamplerYcbcrConversion() override;

		void CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}