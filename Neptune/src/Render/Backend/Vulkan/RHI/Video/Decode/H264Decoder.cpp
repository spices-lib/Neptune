#include "Pchheader.h"
#include "H264Decoder.h"
#include "Render/Backend/Vulkan/VideoParser/Decoder/VulkanH264Decoder.h"

namespace Neptune::Vulkan {

	H264Decoder::H264Decoder(Context& context)
		 : Decoder(context)
	{
        ClientDelegate                                   client;
        client.BeginSequence                           = [&](const VkParserSequenceInfo* info) { return BeginSequence(info); };
        client.DecodePicture                           = [&](VkParserPictureData* pd) { return Decoder::DecodePicture(pd); };
        client.AllocPictureBuffer                      = [&](VkPicIf** picIf) { return AllocPictureBuffer(picIf); };
        client.DisplayPicture                          = [&](VkPicIf* pPicBuff, int64_t timestamp) { return DisplayPicture(pPicBuff, timestamp); };

		m_Decoder = CreateSP<VulkanH264Decoder>(GetContext(), *m_VideoSession, client);

		VkParserInitDecodeParameters                     parameters{};
        parameters.interfaceVersion                    = VK_MAKE_VIDEO_STD_VERSION(0, 9, 9);
        parameters.referenceClockRate                  = 0;
        parameters.errorThreshold                      = 0;
        parameters.outOfBandPictureParameters          = true;
        parameters.isAnnexB                            = false;

		m_Decoder->Initialize(&parameters);
	}

    bool H264Decoder::DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo)
    {
        bool bRet = false;

        nvVideoH264PicParameters h264;
        nvVideoH265PicParameters hevc;
        nvVideoAV1PicParameters av1;
        nvVideoVP9PicParameters vp9;

        if (!pd->pCurrPic) {
            return false;
        }

        const uint32_t PicIdx = ((vkPicBuffBase*)(pd->pCurrPic))->m_picIdx;
        if (PicIdx >= MAX_FRM_CNT) {
            assert(0);
            return false;
        }

        VkParserPerFrameDecodeParameters pictureParams = VkParserPerFrameDecodeParameters();
        VkParserPerFrameDecodeParameters* pCurrFrameDecParams = &pictureParams;
        pCurrFrameDecParams->currPicIdx = PicIdx;
        pCurrFrameDecParams->numSlices = pd->numSlices;
        pCurrFrameDecParams->firstSliceIndex = pd->firstSliceIndex;
        pCurrFrameDecParams->bitstreamDataOffset = pd->bitstreamDataOffset;
        pCurrFrameDecParams->bitstreamDataLen = pd->bitstreamDataLen;
        pCurrFrameDecParams->bitstreamData = pd->bitstreamData;

        VkVideoReferenceSlotInfoKHR referenceSlots[VkParserPerFrameDecodeParameters::MAX_DPB_REF_AND_SETUP_SLOTS];
        VkVideoReferenceSlotInfoKHR setupReferenceSlot = 
        {
            VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR, NULL,
            -1,   // slotIndex
            NULL  // pPictureResource
        };

        pCurrFrameDecParams->decodeFrameInfo.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
        pCurrFrameDecParams->decodeFrameInfo.dstPictureResource.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
        pCurrFrameDecParams->dpbSetupPictureResource.sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;

        //if (m_codecType == VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR) {
        //    const VkParserH264PictureData* const pin = &pd->CodecSpecific.h264;

        //    h264 = nvVideoH264PicParameters();

        //    nvVideoH264PicParameters* const pout = &h264;
        //    VkVideoDecodeH264PictureInfoKHR* pPictureInfo = &h264.pictureInfo;
        //    nvVideoDecodeH264DpbSlotInfo* pDpbRefList = h264.dpbRefList;
        //    StdVideoDecodeH264PictureInfo* pStdPictureInfo = &h264.stdPictureInfo;

        //    pCurrFrameDecParams->pStdPps = pin->pStdPps;
        //    pCurrFrameDecParams->pStdSps = pin->pStdSps;
        //    pCurrFrameDecParams->pStdVps = nullptr;
        //    if (false) {
        //        std::cout << "\n\tCurrent h.264 Picture SPS update : "
        //            << pin->pStdSps->GetUpdateSequenceCount() << std::endl;
        //        std::cout << "\tCurrent h.264 Picture PPS update : "
        //            << pin->pStdPps->GetUpdateSequenceCount() << std::endl;
        //    }

        //    //pDecodePictureInfo->videoFrameType = 0; // pd->CodecSpecific.h264.slice_type;
        //    // FIXME: If mvcext is enabled.
        //    pDecodePictureInfo->viewId = pd->CodecSpecific.h264.mvcext.view_id;

        //    pPictureInfo->pStdPictureInfo = &h264.stdPictureInfo;

        //    pPictureInfo->sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR;

        //    if (!m_outOfBandPictureParameters) {
        //        // In-band h264 Picture Parameters for testing
        //        h264.pictureParameters.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR;
        //        h264.pictureParameters.stdSPSCount = 1;
        //        h264.pictureParameters.pStdSPSs = pin->pStdSps->GetStdH264Sps();
        //        h264.pictureParameters.stdPPSCount = 1;
        //        h264.pictureParameters.pStdPPSs = pin->pStdPps->GetStdH264Pps();
        //        if (m_inlinedPictureParametersUseBeginCoding) {
        //            pCurrFrameDecParams->beginCodingInfoPictureParametersExt = &h264.pictureParameters;
        //            pPictureInfo->pNext = nullptr;
        //        }
        //        else {
        //            pPictureInfo->pNext = &h264.pictureParameters;
        //        }
        //        pCurrFrameDecParams->useInlinedPictureParameters = true;
        //    }
        //    else {
        //        pPictureInfo->pNext = nullptr;
        //    }

        //    pCurrFrameDecParams->decodeFrameInfo.pNext = &h264.pictureInfo;

        //    pStdPictureInfo->pic_parameter_set_id = pin->pic_parameter_set_id; // PPS ID
        //    pStdPictureInfo->seq_parameter_set_id = pin->seq_parameter_set_id; // SPS ID;

        //    pStdPictureInfo->frame_num = (uint16_t)pin->frame_num;
        //    pPictureInfo->sliceCount = pd->numSlices;
        //    uint32_t maxSliceCount = 0;
        //    assert(pd->firstSliceIndex == 0); // No slice and MV modes are supported yet
        //    pPictureInfo->pSliceOffsets = pd->bitstreamData->GetStreamMarkersPtr(pd->firstSliceIndex, maxSliceCount);
        //    assert(maxSliceCount == pd->numSlices);

        //    StdVideoDecodeH264PictureInfoFlags currPicFlags = StdVideoDecodeH264PictureInfoFlags();
        //    currPicFlags.is_intra = (pd->intra_pic_flag != 0);
        //    // 0 = frame picture, 1 = field picture
        //    if (pd->field_pic_flag) {
        //        // 0 = top field, 1 = bottom field (ignored if field_pic_flag = 0)
        //        currPicFlags.field_pic_flag = true;
        //        if (pd->bottom_field_flag) {
        //            currPicFlags.bottom_field_flag = true;
        //        }
        //    }
        //    // Second field of a complementary field pair
        //    if (pd->second_field) {
        //        currPicFlags.complementary_field_pair = true;
        //    }
        //    // Frame is a reference frame
        //    if (pd->ref_pic_flag) {
        //        currPicFlags.is_reference = true;
        //    }
        //    pStdPictureInfo->flags = currPicFlags;
        //    if (!pd->field_pic_flag) {
        //        pStdPictureInfo->PicOrderCnt[0] = pin->CurrFieldOrderCnt[0];
        //        pStdPictureInfo->PicOrderCnt[1] = pin->CurrFieldOrderCnt[1];
        //    }
        //    else {
        //        pStdPictureInfo->PicOrderCnt[pd->bottom_field_flag] = pin->CurrFieldOrderCnt[pd->bottom_field_flag];
        //    }

        //    const uint32_t maxDpbInputSlots = ARRAYSIZE(pin->dpb);
        //    pCurrFrameDecParams->numGopReferenceSlots = FillDpbH264State(
        //        pd, pin->dpb, maxDpbInputSlots, pDpbRefList,
        //        VkParserPerFrameDecodeParameters::MAX_DPB_REF_SLOTS, // 16 reference pictures
        //        referenceSlots, pCurrFrameDecParams->pGopReferenceImagesIndexes,
        //        h264.stdPictureInfo.flags, &setupReferenceSlot.slotIndex);
        //    // TODO: Remove it is for debugging only. Reserved fields must be set to "0".
        //    pout->stdPictureInfo.reserved1 = pCurrFrameDecParams->numGopReferenceSlots;
        //    if (pCurrFrameDecParams->numGopReferenceSlots) {
        //        assert(pCurrFrameDecParams->numGopReferenceSlots <= (int32_t)MAX_DPB_REF_SLOTS);
        //        for (uint32_t dpbEntryIdx = 0; dpbEntryIdx < (uint32_t)pCurrFrameDecParams->numGopReferenceSlots;
        //            dpbEntryIdx++) {
        //            pCurrFrameDecParams->pictureResources[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
        //            referenceSlots[dpbEntryIdx].pPictureResource = &pCurrFrameDecParams->pictureResources[dpbEntryIdx];
        //            assert(pDpbRefList[dpbEntryIdx].IsReference());
        //        }

        //        pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots = referenceSlots;
        //        pCurrFrameDecParams->decodeFrameInfo.referenceSlotCount = pCurrFrameDecParams->numGopReferenceSlots;
        //    }
        //    else {
        //        pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots = NULL;
        //        pCurrFrameDecParams->decodeFrameInfo.referenceSlotCount = 0;
        //    }
        //    assert(!pd->ref_pic_flag || (setupReferenceSlot.slotIndex >= 0));
        //    if (setupReferenceSlot.slotIndex >= 0) {
        //        setupReferenceSlot.pPictureResource = &pCurrFrameDecParams->dpbSetupPictureResource;
        //        pCurrFrameDecParams->decodeFrameInfo.pSetupReferenceSlot = &setupReferenceSlot;

        //        // add the setup slot to the end of referenceSlots
        //        assert((uint32_t)pCurrFrameDecParams->numGopReferenceSlots < MAX_DPB_REF_AND_SETUP_SLOTS);
        //        referenceSlots[pCurrFrameDecParams->numGopReferenceSlots] = setupReferenceSlot;
        //    }

        //}

        DecodePictureWithParameters(pCurrFrameDecParams, pDecodePictureInfo, &pd->CodecSpecific.hevc, pd->pCurrPic);
        return true;
    }

    void H264Decoder::DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic)
    {

    }

    uint32_t H264Decoder::FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots)
    {
        return 1;
    }
}