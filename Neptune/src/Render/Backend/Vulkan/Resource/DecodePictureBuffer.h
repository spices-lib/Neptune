/**
* @file DecodePictureBuffer.h.
* @brief The DecodePictureBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Image.h"

#include <bitset>
#include <queue>

namespace Neptune::Vulkan::Resource {

	/**
	* @brief Vulkan::DecodePictureBuffer Class.
	* This class defines the Vulkan::DecodePictureBuffer behaves.
	*/
	class DecodePictureBuffer : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit DecodePictureBuffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~DecodePictureBuffer() override = default;

		/**
		* @brief Get Unit Handle.
		* 
		* @param[in] index Handle index.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Image::Handle& Handle(uint32_t index) const { return m_Image[index]->Handle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @param[in] index Handle index.
		*
		* @return Returns Unit Handle Interface.
		*/
		const SP<Image> IHandle(uint32_t index) const { return m_Image[index]; }

		/**
		* @brief Get ImageView Unit Handle.
		*
		* @param[in] index Handle index.
		*
		* @return Returns ImageView Unit Handle.
		*/
		const Unit::ImageView::Handle& GetView(uint32_t index) const { return m_Image[index]->GetView(); }

		/**
		* @brief Create Image.
		*
		* @param[in] info VkImageCreateInfo.
		* @param[in] count Image Count.
		*/
		void CreateImage(VkImageCreateInfo& info, uint32_t count);

		/**
		* @brief Create Image View.
		*
		* @param[in] info VkImageViewCreateInfo.
		* @param[in] index Image index.
		*/
		void CreateImageView(VkImageViewCreateInfo& info, uint32_t index) const;

		/**
		* @brief Transform Image Layout.
		*
		* @param[in] newLayout VkImageLayout.
		*/
		void TransitionLayout(VkImageLayout newLayout) const;

		/**
		* @brief Pop a DecodeSlot.
		*
		* @return Returns a DecodeSlot.
		*/
		const uint8_t PopDecodeSlot();

		/**
		* @brief Get current DecodeSlot.
		*
		* @return Returns current DecodeSlot.
		*/
		const uint8_t DecodeSlot() const { return m_DecodeSlot; }

		/**
		* @brief Push DecodeSlot.
		*
		* @param[in] spareSlots Spare Slots.
		*/
		void PushDecodeSlots(const std::bitset<MaxDPBSlots>& spareSlots);

	private:

		std::vector<SP<Image>> m_Image;            // @brief Decode Picture Buffer.
		std::bitset<MaxDPBSlots> m_SlotState;      // @brief All Slot State.
		std::queue<uint8_t> m_SpareSlots;          // @brief Spare Slots.
		uint8_t m_DecodeSlot = 0;                  // @brief Curretn Decode Slot.
		uint8_t m_MaxDPBSlots = MaxDPBSlots;       // @brief Max DPB Slots.
	};
}

#endif