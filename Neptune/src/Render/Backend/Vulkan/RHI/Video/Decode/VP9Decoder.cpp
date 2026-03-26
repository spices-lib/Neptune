#include "Pchheader.h"
#include "VP9Decoder.h"
#include "Render/Backend/Vulkan/VideoParser/Decoder/VulkanAV1Decoder.h"

namespace Neptune::Vulkan {

    VP9Decoder::VP9Decoder(Context& context)
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

    bool VP9Decoder::DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo)
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

        //else if (m_codecType == VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR) {

        //    VkParserVp9PictureData* pin = &pd->CodecSpecific.vp9;

        //    vp9 = nvVideoVP9PicParameters();
        //    StdVideoDecodeVP9PictureInfo* pStdPicInfo = &vp9.stdPictureInfo;
        //    VkVideoDecodeVP9PictureInfoKHR* pVkPicInfo = &vp9.vkPictureInfo;
        //    nvVideoDecodeVP9DpbSlotInfo* pNvDpbSlotInfo = vp9.dpbRefList;

        //    // Copy std data and link pointers
        //    memcpy(pStdPicInfo, &pin->stdPictureInfo, sizeof(StdVideoDecodeVP9PictureInfo));
        //    memcpy(&vp9.stdColorConfig, &pin->stdColorConfig, sizeof(StdVideoVP9ColorConfig));
        //    pStdPicInfo->pColorConfig = &vp9.stdColorConfig;
        //    if (pStdPicInfo->flags.segmentation_enabled == 1) {
        //        memcpy(&vp9.stdSegment, &pin->stdSegmentation, sizeof(StdVideoVP9Segmentation));
        //        pStdPicInfo->pSegmentation = &vp9.stdSegment;
        //    }
        //    memcpy(&vp9.stdLoopFilter, &pin->stdLoopFilter, sizeof(StdVideoVP9LoopFilter));
        //    pStdPicInfo->pLoopFilter = &vp9.stdLoopFilter;

        //    pVkPicInfo->sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_PICTURE_INFO_KHR;
        //    pVkPicInfo->pStdPictureInfo = pStdPicInfo;

        //    VkVideoDecodeInfoKHR* pKhrDecodeInfo = &pCurrFrameDecParams->decodeFrameInfo;
        //    pKhrDecodeInfo->sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
        //    pKhrDecodeInfo->pNext = pVkPicInfo;

        //    // dpb slots
        //    pCurrFrameDecParams->numGopReferenceSlots = FillDpbVP9State(pd,
        //        pin,
        //        pNvDpbSlotInfo,
        //        pStdPicInfo,
        //        9,
        //        referenceSlots,
        //        pCurrFrameDecParams->pGopReferenceImagesIndexes,
        //        &setupReferenceSlot.slotIndex);

        //    if (pCurrFrameDecParams->numGopReferenceSlots) {
        //        assert(pCurrFrameDecParams->numGopReferenceSlots <= (int32_t)MAX_DPB_REF_SLOTS);
        //        for (uint32_t dpbEntryIdx = 0; dpbEntryIdx < (uint32_t)pCurrFrameDecParams->numGopReferenceSlots;
        //            dpbEntryIdx++) {
        //            pCurrFrameDecParams->pictureResources[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
        //            pCurrFrameDecParams->pictureResources[dpbEntryIdx].codedExtent = pNvDpbSlotInfo[dpbEntryIdx].codedExtent;
        //            referenceSlots[dpbEntryIdx].pPictureResource = &pCurrFrameDecParams->pictureResources[dpbEntryIdx];
        //        }

        //        pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots = referenceSlots;
        //        pCurrFrameDecParams->decodeFrameInfo.referenceSlotCount = pCurrFrameDecParams->numGopReferenceSlots;
        //    }
        //    else {
        //        pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots = nullptr;
        //        pCurrFrameDecParams->decodeFrameInfo.referenceSlotCount = 0;
        //    }

        //    assert(!pd->ref_pic_flag || (setupReferenceSlot.slotIndex >= 0));
        //    if (setupReferenceSlot.slotIndex >= 0) {
        //        pCurrFrameDecParams->dpbSetupPictureResource.codedExtent.width = pin->FrameWidth;
        //        pCurrFrameDecParams->dpbSetupPictureResource.codedExtent.height = pin->FrameHeight;
        //        setupReferenceSlot.pPictureResource = &pCurrFrameDecParams->dpbSetupPictureResource;
        //        pCurrFrameDecParams->decodeFrameInfo.pSetupReferenceSlot = &setupReferenceSlot;

        //        // add the setup slot to the end of referenceSlots
        //        assert((uint32_t)pCurrFrameDecParams->numGopReferenceSlots < MAX_DPB_REF_AND_SETUP_SLOTS);
        //        referenceSlots[pCurrFrameDecParams->numGopReferenceSlots] = setupReferenceSlot;
        //    }

        //    // @review: this field seems only useful for debug display, but since AV1 needs a dword, should probably change the interface.
        //    //pDecodePictureInfo->videoFrameType = static_cast<uint16_t>(pin->frame_type);
        //    pDecodePictureInfo->viewId = 0; // @review: Doesn't seem to be used in Vulkan?

        //    bool isKeyFrame = pin->stdPictureInfo.frame_type == STD_VIDEO_VP9_FRAME_TYPE_KEY;
        //    for (size_t i = 0; i < STD_VIDEO_VP9_REFS_PER_FRAME; i++) {
        //        int8_t picIdx = isKeyFrame ? -1 : pin->pic_idx[pin->ref_frame_idx[i]];
        //        if (picIdx < 0) {
        //            pVkPicInfo->referenceNameSlotIndices[i] = -1;
        //            continue;
        //        }

        //        int8_t dpbSlot = GetPicDpbSlot(picIdx);
        //        assert(dpbSlot >= 0);
        //        pVkPicInfo->referenceNameSlotIndices[i] = dpbSlot;
        //    }

        //    pVkPicInfo->uncompressedHeaderOffset = pin->uncompressedHeaderOffset;
        //    pVkPicInfo->compressedHeaderOffset = pin->compressedHeaderOffset;
        //    pVkPicInfo->tilesOffset = pin->tilesOffset;

        //    // Use current frames with and height for display and writing to output
        //    pDecodePictureInfo->displayWidth = pin->FrameWidth;
        //    pDecodePictureInfo->displayHeight = pin->FrameHeight;
        //}
        
        DecodePictureWithParameters(pCurrFrameDecParams, pDecodePictureInfo, &pd->CodecSpecific.hevc, pd->pCurrPic);
        return true;
    }

    void VP9Decoder::DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic)
    {

    }

    uint32_t VP9Decoder::FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots)
    {
        return 1;
    }
}