#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Decoder.h"

namespace Neptune::Vulkan {

	class VP9Decoder : public Decoder
	{
	public:

		VP9Decoder(Context& context);
		~VP9Decoder() override = default;

	private:

		bool DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo) override;

		void DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic) override;

		uint32_t FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots);

	};
}

#endif