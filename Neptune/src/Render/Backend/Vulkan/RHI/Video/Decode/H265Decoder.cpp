#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "H265Decoder.h"
#include "Render/Backend/Vulkan/VideoParser/Decoder/VulkanH265Decoder.h"

namespace Neptune::Vulkan {

	H265Decoder::H265Decoder(Context& context)
		 : Decoder(context)
	{
        ClientDelegate                                   client;
        client.BeginSequence                           = [&](const VkParserSequenceInfo* info) { return BeginSequence(info); };
        client.DecodePicture                           = [&](VkParserPictureData* pd) { return Decoder::DecodePicture(pd); };
        client.AllocPictureBuffer                      = [&](VkPicIf** picIf) { return AllocPictureBuffer(picIf); };
        client.DisplayPicture                          = [&](VkPicIf* pPicBuff, int64_t timestamp) { return DisplayPicture(pPicBuff, timestamp); };

		m_Decoder = CreateSP<VulkanH265Decoder>(GetContext(), *m_VideoSession, client);

		VkParserInitDecodeParameters                     parameters{};
        parameters.interfaceVersion                    = VK_MAKE_VIDEO_STD_VERSION(0, 9, 9);
        parameters.referenceClockRate                  = 0;
        parameters.errorThreshold                      = 0;
        parameters.outOfBandPictureParameters          = true;
        parameters.isAnnexB                            = false;

		m_Decoder->Initialize(&parameters);
	}

    bool H265Decoder::DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo)
    {
        bool bRet = false;

        nvVideoH265PicParameters hevc;

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
        pCurrFrameDecParams->currPicIdx          = PicIdx;
        pCurrFrameDecParams->numSlices           = pd->numSlices;
        pCurrFrameDecParams->firstSliceIndex     = pd->firstSliceIndex;
        pCurrFrameDecParams->bitstreamDataOffset = pd->bitstreamDataOffset;
        pCurrFrameDecParams->bitstreamDataLen    = pd->bitstreamDataLen;
        pCurrFrameDecParams->bitstreamData       = pd->bitstreamData;

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

        if (m_videoFormat.codec == VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR) {
            const VkParserHevcPictureData* const pin = &pd->CodecSpecific.hevc;
            hevc = nvVideoH265PicParameters();
            VkVideoDecodeH265PictureInfoKHR* pPictureInfo = &hevc.pictureInfo;
            StdVideoDecodeH265PictureInfo* pStdPictureInfo = &hevc.stdPictureInfo;
            nvVideoDecodeH265DpbSlotInfo* pDpbRefList = hevc.dpbRefList;

            pCurrFrameDecParams->pStdPps = pin->pStdPps;
            pCurrFrameDecParams->pStdSps = pin->pStdSps;
            pCurrFrameDecParams->pStdVps = pin->pStdVps;

            pPictureInfo->sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
            pPictureInfo->pNext = nullptr;

            pPictureInfo->pStdPictureInfo = &hevc.stdPictureInfo;
            pCurrFrameDecParams->decodeFrameInfo.pNext = &hevc.pictureInfo;

            //pDecodePictureInfo->videoFrameType = 0; // pd->CodecSpecific.hevc.SliceType;
            if (pd->CodecSpecific.hevc.mv_hevc_enable) {
                pDecodePictureInfo->viewId = pd->CodecSpecific.hevc.nuh_layer_id;
            }
            else {
                pDecodePictureInfo->viewId = 0;
            }

            pPictureInfo->sliceSegmentCount = pd->numSlices;
            uint32_t maxSliceCount = 0;
            assert(pd->firstSliceIndex == 0); // No slice and MV modes are supported yet
            pPictureInfo->pSliceSegmentOffsets = pd->bitstreamData->GetStreamMarkersPtr(pd->firstSliceIndex, maxSliceCount);
            assert(maxSliceCount == pd->numSlices);

            pStdPictureInfo->pps_pic_parameter_set_id = pin->pic_parameter_set_id;       // PPS ID
            pStdPictureInfo->pps_seq_parameter_set_id = pin->seq_parameter_set_id;       // SPS ID
            pStdPictureInfo->sps_video_parameter_set_id = pin->vps_video_parameter_set_id; // VPS ID
 
            // hevc->irapPicFlag = m_slh.nal_unit_type >= NUT_BLA_W_LP &&
            // m_slh.nal_unit_type <= NUT_CRA_NUT;
            pStdPictureInfo->flags.IrapPicFlag = pin->IrapPicFlag; // Intra Random Access Point for current picture.
            // hevc->idrPicFlag = m_slh.nal_unit_type == NUT_IDR_W_RADL ||
            // m_slh.nal_unit_type == NUT_IDR_N_LP;
            pStdPictureInfo->flags.IdrPicFlag = pin->IdrPicFlag; // Instantaneous Decoding Refresh for current picture.
            pStdPictureInfo->flags.IsReference = 1;
            // NumBitsForShortTermRPSInSlice = s->sh.short_term_rps ?
            // s->sh.short_term_ref_pic_set_size : 0
            pStdPictureInfo->NumBitsForSTRefPicSetInSlice = pin->NumBitsForShortTermRPSInSlice;

            // NumDeltaPocsOfRefRpsIdx = s->sh.short_term_rps ?
            // s->sh.short_term_rps->rps_idx_num_delta_pocs : 0
            pStdPictureInfo->NumDeltaPocsOfRefRpsIdx = pin->NumDeltaPocsOfRefRpsIdx;
            pStdPictureInfo->PicOrderCntVal = pin->CurrPicOrderCntVal;

            pCurrFrameDecParams->numGopReferenceSlots = FillDpbState(pd, pin, pStdPictureInfo, referenceSlots);

            if (pCurrFrameDecParams->numGopReferenceSlots) {
                assert(pCurrFrameDecParams->numGopReferenceSlots <= (int32_t)MAX_DPB_REF_SLOTS);
                for (uint32_t dpbEntryIdx = 0; dpbEntryIdx < (uint32_t)pCurrFrameDecParams->numGopReferenceSlots;
                    dpbEntryIdx++) {
                    pCurrFrameDecParams->pictureResources[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
                    referenceSlots[dpbEntryIdx].pPictureResource = &pCurrFrameDecParams->pictureResources[dpbEntryIdx];
                    //assert(pDpbRefList[dpbEntryIdx].IsReference());
                }

                pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots = referenceSlots;
                pCurrFrameDecParams->decodeFrameInfo.referenceSlotCount = pCurrFrameDecParams->numGopReferenceSlots;
            }
            else {
                pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots = NULL;
                pCurrFrameDecParams->decodeFrameInfo.referenceSlotCount = 0;
            }
        }

        DecodePictureWithParameters(pCurrFrameDecParams, pDecodePictureInfo, &pd->CodecSpecific.hevc, pd->pCurrPic);
        return true;
    }

    uint32_t H265Decoder::FillDpbState(const VkParserPictureData* pd, const VkParserHevcPictureData* pin, StdVideoDecodeH265PictureInfo* pStdPictureInfo, VkVideoReferenceSlotInfoKHR* pReferenceSlots)
    {
        std::bitset<MaxDPBSlots> inUseSlots;

        int count = 0;
        for (int i = 0; i < 16; i++)
        {
            auto pic = static_cast<VkPicIf2*>(pin->RefPics[i]);
            
            if (!pic) continue;

            inUseSlots.set(pic->m_picIdx);

            pReferenceSlots[count++].slotIndex = pic->m_picIdx;
        }

        auto pic = static_cast<VkPicIf2*>(pd->pCurrPic);

        pic->m_displayOrder = pStdPictureInfo->PicOrderCntVal;

        inUseSlots.set(pic->m_picIdx);

        m_VideoSession->DPB().PushDecodeSlots(inUseSlots.flip());

        {
            uint32_t iter = 0;
            for (int32_t i = 0; i < pin->NumPocStCurrBefore; i++)
            {
                auto idx = pin->RefPicSetStCurrBefore[i];
                auto pic = static_cast<VkPicIf2*>(pin->RefPics[idx]);

                if (!pic) continue;

                pStdPictureInfo->RefPicSetStCurrBefore[iter++] = pic->m_picIdx & 0xf;
            }
            while (iter < 8) 
            {
                pStdPictureInfo->RefPicSetStCurrBefore[iter++] = 0xff;
            }
        }

        {
            uint32_t iter = 0;
            for (int32_t i = 0; i < pin->NumPocStCurrAfter; i++)
            {
                auto idx = pin->RefPicSetStCurrAfter[i];
                auto pic = static_cast<VkPicIf2*>(pin->RefPics[idx]);

                if (!pic) continue;

                pStdPictureInfo->RefPicSetStCurrAfter[iter++] = pic->m_picIdx & 0xf;
            }
            while (iter < 8) 
            {
                pStdPictureInfo->RefPicSetStCurrAfter[iter++] = 0xff;
            }
        }

        {
            uint32_t iter = 0;
            for (int32_t i = 0; i < pin->NumPocLtCurr; i++)
            {
                auto idx = pin->RefPicSetLtCurr[i];
                auto pic = static_cast<VkPicIf2*>(pin->RefPics[idx]);

                if (!pic) continue;

                pStdPictureInfo->RefPicSetLtCurr[iter++] = pic->m_picIdx & 0xf;
            }
            while (iter < 8)
            {
                pStdPictureInfo->RefPicSetLtCurr[iter++] = 0xff;
            }
        }

        return count;
    }

    void H265Decoder::DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic)
    {
        auto range = pCurrFrameDecParams->bitstreamDataLen;
        range = ((range + (256 - 1)) & ~(256 - 1));
        pCurrFrameDecParams->bitstreamDataLen = range;

        StdVideoDecodeH265ReferenceInfo     refInfo[MaxDPBSlots]{};
        VkVideoDecodeH265DpbSlotInfoKHR     slotInfo[MaxDPBSlots]{};
        VkVideoPictureResourceInfoKHR       pics[MaxDPBSlots]{};
        VkVideoReferenceSlotInfoKHR         info[MaxDPBSlots]{};

        auto refCount = pCurrFrameDecParams->numGopReferenceSlots;
        auto refId = 0;
        for (int i = 0; i < refCount; i++)
        {
            while (!pin->RefPics[refId]) { ++refId; }

            refInfo[i].flags.used_for_long_term_reference      = 0;
            refInfo[i].flags.unused_for_reference              = 0;
            refInfo[i].PicOrderCntVal                          = static_cast<VkPicIf2*>(pin->RefPics[refId++])->m_displayOrder;

            slotInfo[i].sType                                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
            slotInfo[i].pStdReferenceInfo                      = &refInfo[i];

            pics[i].sType                                      = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
            pics[i].baseArrayLayer                             = 0;
            pics[i].codedExtent                                = { m_videoFormat.coded_width, m_videoFormat.coded_height };
            pics[i].imageViewBinding                           = m_VideoSession->DPB().GetView(pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots[i].slotIndex);

            info[i].sType                                      = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
            info[i].slotIndex                                  = pCurrFrameDecParams->decodeFrameInfo.pReferenceSlots[i].slotIndex;
            info[i].pPictureResource                           = &pics[i];
            info[i].pNext                                      = &slotInfo[i];
        }

        refInfo[refCount].flags.used_for_long_term_reference   = 0;
        refInfo[refCount].flags.unused_for_reference           = 0;
        refInfo[refCount].PicOrderCntVal                       = static_cast<VkPicIf2*>(pic)->m_displayOrder;

        slotInfo[refCount].sType                               = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
        slotInfo[refCount].pStdReferenceInfo                   = &refInfo[refCount];

        pics[refCount].sType                                   = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR;
        pics[refCount].baseArrayLayer                          = 0;
        pics[refCount].codedExtent                             = { m_videoFormat.coded_width, m_videoFormat.coded_height };
        pics[refCount].imageViewBinding                        = m_VideoSession->DPB().GetView(m_VideoSession->DPB().DecodeSlot());
                              
        info[refCount].sType                                   = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
        info[refCount].slotIndex                               = -1;
        info[refCount].pPictureResource                        = &pics[refCount];
        info[refCount].pNext                                   = &slotInfo[refCount];

        CmdDecode(pCurrFrameDecParams, pics, info);
    }

}

#endif