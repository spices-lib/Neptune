/**
* @file ImageView.cpp.
* @brief The ImageView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ImageView.h"

namespace Neptune::Vulkan::Unit {

	ImageView::~ImageView()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkDestroyImageView(m_Device, m_Handle, nullptr);
	}

	void ImageView::CreateImageView(VkDevice device, const VkImageViewCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateImageView(m_Device, &info, nullptr, &m_Handle))
	}
}