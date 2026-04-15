/**
* @file DecodeBuffer.cpp.
* @brief The DecodeBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DecodePictureBuffer.h"

namespace Neptune::Vulkan {

	void DecodePictureBuffer::CreateImage(VkImageCreateInfo& info, uint32_t count)
	{
		NEPTUNE_PROFILE_ZONE

		for (int i = 0; i < count; i++)
		{
			auto image = CreateSP<Image>(GetContext());

			image->CreateImage(info, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			image->SetName("DecodeImageBuffer");

			m_Image.emplace_back(image);
		}

		m_MaxDPBSlots = count;

		m_SlotState.flip();

		for (int i = 0; i < m_MaxDPBSlots; i++)
		{
			m_SpareSlots.push(i);
		}
	}

	void DecodePictureBuffer::CreateImageView(VkImageViewCreateInfo& info, uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Image[index]->CreateImageView(info);

		m_Image[index]->SetName("DecodeImageBuffer");
	}

	void DecodePictureBuffer::TransitionLayout(VkImageLayout newLayout) const
	{
		NEPTUNE_PROFILE_ZONE

		for (int i = 0; i < m_Image.size(); i++)
		{
			m_Image[i]->TransitionLayout(newLayout);
		}
	}

	const uint8_t DecodePictureBuffer::PopDecodeSlot()
	{
		NEPTUNE_PROFILE_ZONE

		m_DecodeSlot = m_SpareSlots.front();

		m_SpareSlots.pop();

		m_SlotState.set(m_DecodeSlot, false);

		return m_DecodeSlot;
	}

	void DecodePictureBuffer::PushDecodeSlots(const std::bitset<MaxDPBSlots>& spareSlots)
	{
		NEPTUNE_PROFILE_ZONE

		for (int i = 0; i < m_MaxDPBSlots; i++)
		{
			if (spareSlots.test(i) && !m_SlotState.test(i))
			{
				m_SpareSlots.push(i);
				m_SlotState.set(i, true);
			}
		}
	}
}

#endif