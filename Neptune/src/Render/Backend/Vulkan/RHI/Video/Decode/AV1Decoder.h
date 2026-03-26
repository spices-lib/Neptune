#pragma once
#include "Decoder.h"

namespace Neptune::Vulkan {

	class AV1Decoder : public Decoder
	{
	public:

		AV1Decoder(Context& context);
		~AV1Decoder() override = default;

	private:

		bool DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo) override;

		void DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic) override;

		uint32_t FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots);

	};
}