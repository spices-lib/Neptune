#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	class OpticalFlowSession : public Unit<VkOpticalFlowSessionNV, VkObjectType::VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV>
	{
	public:

		using Handle = Unit::Handle;

	public:

		OpticalFlowSession() : Unit() {}

		~OpticalFlowSession() override;

		void SetFunctor(PFN_vkCreateOpticalFlowSessionNV create, PFN_vkDestroyOpticalFlowSessionNV destroy, PFN_vkBindOpticalFlowSessionImageNV bind);

		void CreateOpticalFlowSession(VkDevice device, const VkOpticalFlowSessionCreateInfoNV& info);

		void BindOpticalFlowSessionImage(VkOpticalFlowSessionBindingPointNV bindPoint, VkImageView view, VkImageLayout layout) const;

	private:

		VkDevice                            m_Device = VK_NULL_HANDLE;
		PFN_vkCreateOpticalFlowSessionNV    vkCreateOpticalFlowSessionNV;
		PFN_vkDestroyOpticalFlowSessionNV   vkDestroyOpticalFlowSessionNV;
		PFN_vkBindOpticalFlowSessionImageNV vkBindOpticalFlowSessionImageNV;
	};
}