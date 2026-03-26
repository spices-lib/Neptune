#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Image.h"
#include <bitset>
#include <queue>

namespace Neptune::Vulkan {

	class DecodePictureBuffer : public ContextAccessor
	{
	public:

		DecodePictureBuffer(Context& context) : ContextAccessor(context) {}
		~DecodePictureBuffer() override = default;

		const Unit::Image::Handle& Handle(uint32_t index) const { return m_Image[index]->Handle(); }

		Image* IHandle(uint32_t index) { return m_Image[index].get(); }

		const Unit::ImageView::Handle& GetView(uint32_t index) const { return m_Image[index]->GetView(); }

		void CreateImage(VkImageCreateInfo& info, uint32_t count);

		void CreateImageView(VkImageViewCreateInfo& info, uint32_t index);

		void TransitionLayout(VkImageLayout newLayout);

		uint8_t PopDecodeSlot();

		uint8_t DecodeSlot() const { return m_DecodeSlot; }

		void PushDecodeSlots(const std::bitset<MaxDPBSlots>& spareSlots);

	private:

		std::vector<SP<Image>> m_Image;
		std::bitset<MaxDPBSlots> m_SlotState;
		std::queue<uint8_t> m_SpareSlots;
		uint8_t m_DecodeSlot = 0;
		uint8_t m_MaxDPBSlots = MaxDPBSlots;
	};
}