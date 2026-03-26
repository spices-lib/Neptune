#include "Pchheader.h"
#include "AV1Decoder.h"
#include "Render/Backend/Vulkan/VideoParser/Decoder/VulkanAV1Decoder.h"

namespace Neptune::Vulkan {

    AV1Decoder::AV1Decoder(Context& context)
		 : Decoder(context)
	{
        ClientDelegate                                   client;
        client.BeginSequence                           = [&](const VkParserSequenceInfo* info) { return BeginSequence(info); };
        client.DecodePicture                           = [&](VkParserPictureData* pd) { return Decoder::DecodePicture(pd); };
        client.AllocPictureBuffer                      = [&](VkPicIf** picIf) { return AllocPictureBuffer(picIf); };
        client.DisplayPicture                          = [&](VkPicIf* pPicBuff, int64_t timestamp) { return DisplayPicture(pPicBuff, timestamp); };

		m_Decoder = CreateSP<VulkanAV1Decoder>(GetContext(), *m_VideoSession, client);

		VkParserInitDecodeParameters                     parameters{};
        parameters.interfaceVersion                    = VK_MAKE_VIDEO_STD_VERSION(0, 9, 9);
        parameters.referenceClockRate                  = 0;
        parameters.errorThreshold                      = 0;
        parameters.outOfBandPictureParameters          = true;
        parameters.isAnnexB                            = false;

		m_Decoder->Initialize(&parameters);
	}

    bool AV1Decoder::DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo)
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

        //else if (m_codecType == VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR) {
        //    VkParserAv1PictureData* pin = &pd->CodecSpecific.av1;

        //    av1 = nvVideoAV1PicParameters();
        //    VkVideoDecodeAV1PictureInfoKHR* pPictureInfo = &av1.pictureInfo;
        //    av1.pictureInfo.pStdPictureInfo = &av1.stdPictureInfo;
        //    StdVideoDecodeAV1PictureInfo* pStdPictureInfo = &av1.stdPictureInfo;

        //    pCurrFrameDecParams->pStdPps = nullptr;
        //    pCurrFrameDecParams->pStdSps = pin->pStdSps;
        //    pCurrFrameDecParams->pStdVps = nullptr;

        //    if (false) {
        //        std::cout << "\n\tCurrent AV1 Picture SPS update : "
        //            << pin->pStdSps->GetUpdateSequenceCount() << std::endl;
        //    }

        //    nvVideoDecodeAV1DpbSlotInfo* dpbSlotsAv1 = av1.dpbRefList;
        //    pCurrFrameDecParams->numGopReferenceSlots =
        //        FillDpbAV1State(pd,
        //            pin,
        //            dpbSlotsAv1,
        //            pStdPictureInfo,
        //            9,
        //            referenceSlots,
        //            pCurrFrameDecParams->pGopReferenceImagesIndexes,
        //            &setupReferenceSlot.slotIndex);

        //    if (pCurrFrameDecParams->numGopReferenceSlots) {
        //        assert(pCurrFrameDecParams->numGopReferenceSlots <= (int32_t)MAX_DPB_REF_SLOTS);
        //        for (uint32_t dpbEntryIdx = 0; dpbEntryIdx < (uint32_t)pCurrFrameDecParams->numGopReferenceSlots;
        //            dpbEntryIdx++) {
        //            pCurrFrameDecParams->pictureResources[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
        //            referenceSlots[dpbEntryIdx].pPictureResource = &pCurrFrameDecParams->pictureResources[dpbEntryIdx];
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

        //    // @review: this field seems only useful for debug display, but since AV1 needs a dword, should probably change the interface.
        //    //pDecodePictureInfo->videoFrameType = static_cast<uint16_t>(pin->frame_type);
        //    pDecodePictureInfo->viewId = 0; // @review: Doesn't seem to be used in Vulkan?

        //    pPictureInfo->sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PICTURE_INFO_KHR;
        //    pCurrFrameDecParams->decodeFrameInfo.pNext = &av1.pictureInfo;

        //    bool isKeyFrame = pin->std_info.frame_type == STD_VIDEO_AV1_FRAME_TYPE_KEY;
        //    for (size_t i = 0; i < STD_VIDEO_AV1_REFS_PER_FRAME; i++) {
        //        int8_t picIdx = isKeyFrame ? -1 : pin->pic_idx[pin->ref_frame_idx[i]];
        //        if (picIdx < 0) {
        //            pPictureInfo->referenceNameSlotIndices[i] = -1;
        //            continue;
        //        }

        //        int8_t dpbSlot = GetPicDpbSlot(picIdx);
        //        assert(dpbSlot >= 0);
        //        pPictureInfo->referenceNameSlotIndices[i] = dpbSlot;
        //    }

        //    pPictureInfo->pTileOffsets = pin->tileOffsets;
        //    pPictureInfo->pTileSizes = pin->tileSizes;
        //    pPictureInfo->tileCount = pin->khr_info.tileCount;
        //    StdVideoDecodeAV1PictureInfo& hdr = av1.stdPictureInfo;

        //    memcpy(&hdr, &pin->std_info, sizeof(hdr));
        //    hdr.pTileInfo = &pin->tileInfo;
        //    hdr.pQuantization = &pin->quantization;
        //    hdr.pSegmentation = &pin->segmentation;
        //    hdr.pLoopFilter = &pin->loopFilter;
        //    hdr.pCDEF = &pin->CDEF;
        //    hdr.pLoopRestoration = &pin->loopRestoration;
        //    hdr.pGlobalMotion = &pin->globalMotion;
        //    hdr.pFilmGrain = &pin->filmGrain;

        //    pin->tileInfo.pWidthInSbsMinus1 = pin->width_in_sbs_minus_1;
        //    pin->tileInfo.pHeightInSbsMinus1 = pin->height_in_sbs_minus_1;
        //    pin->tileInfo.pMiColStarts = pin->MiColStarts;
        //    pin->tileInfo.pMiRowStarts = pin->MiRowStarts;

        //    pDecodePictureInfo->flags.applyFilmGrain = pin->std_info.flags.apply_grain;

        //}
        
        DecodePictureWithParameters(pCurrFrameDecParams, pDecodePictureInfo, &pd->CodecSpecific.hevc, pd->pCurrPic);
        return true;
    }

    void AV1Decoder::DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic)
    {

    }

    uint32_t AV1Decoder::FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots)
    {
        return 1;
    }
}