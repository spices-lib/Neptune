/**
* @file VideoSessionParameters.cpp.
* @brief The VideoSessionParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "VideoSessionParameters.h"

namespace Neptune::Vulkan::Unit {

	VideoSessionParameters::~VideoSessionParameters()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyVideoSessionParametersKHR(m_Device, m_Handle, nullptr);
	}

	void VideoSessionParameters::SetFunctor(PFN_vkCreateVideoSessionParametersKHR create, PFN_vkDestroyVideoSessionParametersKHR destroy, PFN_vkUpdateVideoSessionParametersKHR update)
	{
		NEPTUNE_PROFILE_ZONE

		vkCreateVideoSessionParametersKHR  = create;
		vkDestroyVideoSessionParametersKHR = destroy;
		vkUpdateVideoSessionParametersKHR  = update;
	}

	void VideoSessionParameters::CreateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersCreateInfoKHR& createInfo)
	{
		NEPTUNE_PROFILE_ZONE
			
		assert(device && !m_Handle);

		m_Device = device;

		VK_CHECK(vkCreateVideoSessionParametersKHR(m_Device, &createInfo, nullptr, &m_Handle))
	}

	void VideoSessionParameters::UpdateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersUpdateInfoKHR& updateInfo) const
	{
		NEPTUNE_PROFILE_ZONE

		VK_CHECK(vkUpdateVideoSessionParametersKHR(m_Device, m_Handle, &updateInfo))
	}
}

#endif