#include "Pchheader.h"
#include "DecodePictureBuffer.h"

namespace Neptune::Vulkan {

	void DecodePictureBuffer::CreateImage(VkImageCreateInfo& info, uint32_t count)
	{
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

	void DecodePictureBuffer::CreateImageView(VkImageViewCreateInfo& info, uint32_t index)
	{
		m_Image[index]->CreateImageView(info);

		m_Image[index]->SetName("DecodeImageBuffer");
	}

	void DecodePictureBuffer::TransitionLayout(VkImageLayout newLayout)
	{
		for (int i = 0; i < m_Image.size(); i++)
		{
			m_Image[i]->TransitionLayout(newLayout);
		}
	}

	uint8_t DecodePictureBuffer::PopDecodeSlot()
	{
		m_DecodeSlot = m_SpareSlots.front();

		m_SpareSlots.pop();

		m_SlotState.set(m_DecodeSlot, false);

		return m_DecodeSlot;
	}

	void DecodePictureBuffer::PushDecodeSlots(const std::bitset<MaxDPBSlots>& spareSlots)
	{
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