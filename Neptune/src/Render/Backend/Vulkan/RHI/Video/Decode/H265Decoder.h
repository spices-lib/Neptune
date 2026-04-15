#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Decoder.h"

namespace Neptune::Vulkan {

	class H265Decoder : public Decoder
	{
	public:

		H265Decoder(Context& context);
		~H265Decoder() override = default;

	private:

		bool DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo) override;

		void DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic) override;

		uint32_t FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots);

	};
}

#endif