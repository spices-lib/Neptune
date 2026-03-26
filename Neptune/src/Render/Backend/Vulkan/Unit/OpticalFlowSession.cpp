#include "Pchheader.h"
#include "OpticalFlowSession.h"

namespace Neptune::Vulkan::Unit {

	void OpticalFlowSession::SetFunctor(PFN_vkCreateOpticalFlowSessionNV create, PFN_vkDestroyOpticalFlowSessionNV destroy, PFN_vkBindOpticalFlowSessionImageNV bind)
	{
		vkCreateOpticalFlowSessionNV    = create;
		vkDestroyOpticalFlowSessionNV   = destroy;
		vkBindOpticalFlowSessionImageNV = bind;
	}	

	OpticalFlowSession::~OpticalFlowSession()
	{
		if (!m_Handle) return;

		vkDestroyOpticalFlowSessionNV(m_Device, m_Handle, nullptr);
	}

	void OpticalFlowSession::CreateOpticalFlowSession(VkDevice device, const VkOpticalFlowSessionCreateInfoNV& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateOpticalFlowSessionNV(m_Device, &info, nullptr, &m_Handle));
	}

	void OpticalFlowSession::BindOpticalFlowSessionImage(VkOpticalFlowSessionBindingPointNV bindPoint, VkImageView view, VkImageLayout layout) const
	{
		VK_CHECK(vkBindOpticalFlowSessionImageNV(m_Device, m_Handle, bindPoint, view, layout))
	}

}