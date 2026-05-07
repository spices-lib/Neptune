#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Decoder.h"
#include "H265Decoder.h"
#include "H264Decoder.h"
#include "AV1Decoder.h"
#include "VP9Decoder.h"
#include "Feature/Video/VideoOperation.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/VideoParser/STD/nvVulkanVideoUtils.h"
#include "Render/Backend/Vulkan/VideoParser/STD/VkVideoCoreProfile.h"
#include "Render/Backend/Vulkan/RHI/CmdList2.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/Resource/QueryPool.h"

#include <bitset>

namespace Neptune::Vulkan {

	SP<Decoder> Decoder::Create(Context& context, void* payload)
	{
        NEPTUNE_PROFILE_ZONE

		VideoOperation& op = *static_cast<VideoOperation*>(payload);

		switch(op)
		{
		    case VideoOperation::DecodeVP9:  return CreateSP<VP9Decoder>(context);
		    case VideoOperation::DecodeH264: return CreateSP<H264Decoder>(context);
		    case VideoOperation::DecodeH265: return CreateSP<H265Decoder>(context);
		    case VideoOperation::DecodeAV1:  return CreateSP<AV1Decoder>(context);
		    default:
		    {
			    NEPTUNE_CORE_ERROR("Vulkan::Decoder::Create: Unsupported VideoOperation")
			    return nullptr;
		    }
		}
	}

    Decoder::Decoder(Context& context)
        : ContextAccessor(context)
        , m_dpb(3)
    {
        m_VideoSession = CreateSP<Resource::VideoSession>(context);
    }

    int32_t Decoder::BeginSequence(const VkParserSequenceInfo* pnvsi)
    {
        bool sequenceUpdate = ((m_nvsi.nMaxWidth != 0) && (m_nvsi.nMaxHeight != 0)) ? true : false;

        uint32_t maxDpbSlots = (pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR) ?
            MAX_DPB_REF_AND_SETUP_SLOTS : MAX_DPB_REF_SLOTS;

        if (pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR) {
            maxDpbSlots = STD_VIDEO_AV1_NUM_REF_FRAMES + 1;
            if ((pnvsi->nCodedWidth <= m_nvsi.nCodedWidth) && (pnvsi->nCodedHeight <= m_nvsi.nCodedHeight)) {
                return 1;
            }
        }
        else if (pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR) {
            maxDpbSlots = STD_VIDEO_VP9_NUM_REF_FRAMES + 1;
            if ((pnvsi->nMaxWidth <= m_nvsi.nMaxWidth) && (pnvsi->nMaxHeight <= m_nvsi.nMaxHeight)) {
                return 1;
            }
        }

        uint32_t configDpbSlots = (pnvsi->nMinNumDpbSlots > 0) ? pnvsi->nMinNumDpbSlots : maxDpbSlots;
        configDpbSlots = std::min<uint32_t>(configDpbSlots, maxDpbSlots);

        bool sequenceReconfigureFormat = false;
        bool sequenceReconfigureCodedExtent = false;
        if (sequenceUpdate) {
            if ((pnvsi->eCodec != m_nvsi.eCodec) ||
                (pnvsi->nChromaFormat != m_nvsi.nChromaFormat) || (pnvsi->uBitDepthLumaMinus8 != m_nvsi.uBitDepthLumaMinus8) ||
                (pnvsi->uBitDepthChromaMinus8 != m_nvsi.uBitDepthChromaMinus8) ||
                (pnvsi->bProgSeq != m_nvsi.bProgSeq)) {
                sequenceReconfigureFormat = true;
            }

            if ((pnvsi->nCodedWidth != m_nvsi.nCodedWidth) || (pnvsi->nCodedHeight != m_nvsi.nCodedHeight)) {
                sequenceReconfigureCodedExtent = true;
            }
        }

        m_nvsi = *pnvsi;
        m_nvsi.nMaxWidth  = std::max(m_nvsi.nMaxWidth , m_nvsi.nDisplayWidth);
        m_nvsi.nMaxHeight = std::max(m_nvsi.nMaxHeight, m_nvsi.nDisplayHeight);

        m_maxNumDecodeSurfaces = pnvsi->nMinNumDecodeSurfaces;

        uint8_t raw_seqhdr_data[1024];

        VkParserDetectedVideoFormat                     detectedFormat{};
        detectedFormat.sequenceUpdate                 = sequenceUpdate;
        detectedFormat.sequenceReconfigureFormat      = sequenceReconfigureFormat;
        detectedFormat.sequenceReconfigureCodedExtent = sequenceReconfigureCodedExtent;
        detectedFormat.codec                          = pnvsi->eCodec;
        detectedFormat.frame_rate.numerator           = NV_FRAME_RATE_NUM(pnvsi->frameRate);
        detectedFormat.frame_rate.denominator         = NV_FRAME_RATE_DEN(pnvsi->frameRate);
        detectedFormat.progressive_sequence           = pnvsi->bProgSeq;
        detectedFormat.coded_width                    = pnvsi->nCodedWidth;
        detectedFormat.coded_height                   = pnvsi->nCodedHeight;
        detectedFormat.display_area.right             = pnvsi->nDisplayWidth;
        detectedFormat.display_area.bottom            = pnvsi->nDisplayHeight;
        detectedFormat.filmGrainUsed                  = pnvsi->hasFilmGrain;

        if ((StdChromaFormatIdc)pnvsi->nChromaFormat == chroma_format_idc_420) {
            detectedFormat.chromaSubsampling          = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
        }
        else if ((StdChromaFormatIdc)pnvsi->nChromaFormat == chroma_format_idc_422) {
            detectedFormat.chromaSubsampling          = VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR;
        }
        else if ((StdChromaFormatIdc)pnvsi->nChromaFormat == chroma_format_idc_444) {
            detectedFormat.chromaSubsampling          = VK_VIDEO_CHROMA_SUBSAMPLING_444_BIT_KHR;
        }
        else {
            assert(!"Invalid chroma sub-sampling format");
        }

        switch (pnvsi->uBitDepthLumaMinus8) {
        case 0:
            detectedFormat.lumaBitDepth               = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
            break;
        case 2:
            detectedFormat.lumaBitDepth               = VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR;
            break;
        case 4:
            detectedFormat.lumaBitDepth               = VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR;
            break;
        default:
            assert(false);
        }

        switch (pnvsi->uBitDepthChromaMinus8) {
        case 0:
            detectedFormat.chromaBitDepth             = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
            break;
        case 2:
            detectedFormat.chromaBitDepth             = VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR;
            break;
        case 4:
            detectedFormat.chromaBitDepth             = VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR;
            break;
        default:
            assert(false);
        }

        detectedFormat.bit_depth_luma_minus8                                   = pnvsi->uBitDepthLumaMinus8;
        detectedFormat.bit_depth_chroma_minus8                                 = pnvsi->uBitDepthChromaMinus8;
        detectedFormat.bitrate                                                 = pnvsi->lBitrate;
        detectedFormat.display_aspect_ratio.x                                  = pnvsi->lDARWidth;
        detectedFormat.display_aspect_ratio.y                                  = pnvsi->lDARHeight;
        detectedFormat.video_signal_description.video_format                   = pnvsi->lVideoFormat;
        detectedFormat.video_signal_description.video_full_range_flag          = pnvsi->uVideoFullRange;
        detectedFormat.video_signal_description.color_primaries                = pnvsi->lColorPrimaries;
        detectedFormat.video_signal_description.transfer_characteristics       = pnvsi->lTransferCharacteristics;
        detectedFormat.video_signal_description.matrix_coefficients            = pnvsi->lMatrixCoefficients;
        detectedFormat.seqhdr_data_length                                      = (uint32_t)std::min((size_t)pnvsi->cbSequenceHeader, sizeof(raw_seqhdr_data));
        detectedFormat.minNumDecodeSurfaces                                    = pnvsi->nMinNumDecodeSurfaces;
        detectedFormat.maxNumDpbSlots                                          = configDpbSlots;
        detectedFormat.codecProfile                                            = pnvsi->codecProfile;

        if (detectedFormat.seqhdr_data_length > 0) {
            memcpy(raw_seqhdr_data, pnvsi->SequenceHeaderData, detectedFormat.seqhdr_data_length);
        }
        int32_t maxDecodeRTs = StartVideoSequence(&detectedFormat);
        // nDecodeRTs <= 0 means SequenceCallback failed
        // nDecodeRTs  = 1 means SequenceCallback succeeded
        // nDecodeRTs  > 1 means we need to overwrite the MaxNumDecodeSurfaces
        if (maxDecodeRTs <= 0) {
            return 0;
        }
        // MaxNumDecodeSurface may not be correctly calculated by the client while
        // parser creation so overwrite it with NumDecodeSurface. (only if nDecodeRT
        // > 1)
        if (maxDecodeRTs > 1) {
            m_maxNumDecodeSurfaces = maxDecodeRTs;
        }

        // AV1 and VP9 support cross-sequence referencing.
        if (pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR ||
            pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR)
        {
            m_maxNumDpbSlots = m_dpb.Init(configDpbSlots, false /* reconfigure the DPB size if true */);
            // Ensure the picture map is empited, so that DPB slot management doesn't get confused in-between sequences.
        }
        else if (pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR ||
            pnvsi->eCodec == VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR)
        {
            if (m_dpb.getMaxSize() < configDpbSlots)
            {
                m_maxNumDpbSlots = m_dpb.Init(configDpbSlots, false);
            }
        }
        else {
            assert(!"Codec DPB management not fully implemented");
        }

        return m_maxNumDecodeSurfaces;
    }
    
    int32_t Decoder::StartVideoSequence(VkParserDetectedVideoFormat* pVideoFormat)
    {
        m_codedExtent.width  = pVideoFormat->coded_width;
        m_codedExtent.height = pVideoFormat->coded_height;

        auto physicalDevice = GetContext().Get<IPhysicalDevice>();

        VkVideoCodecOperationFlagBitsKHR videoCodec = pVideoFormat->codec;

        VkVideoCoreProfile videoProfile(videoCodec, pVideoFormat->chromaSubsampling, pVideoFormat->lumaBitDepth, pVideoFormat->chromaBitDepth, pVideoFormat->codecProfile);

        m_VideoSession->CreateVideoSession(*videoProfile.GetProfile(), pVideoFormat->coded_width, pVideoFormat->coded_height, pVideoFormat->maxNumDpbSlots);

        if (m_DecodeRT)
        {
            m_VideoSession->CreateDecodeRenderTarget(m_DecodeRT, *videoProfile.GetProfile(), pVideoFormat->coded_width, pVideoFormat->coded_height);
        }

        if (m_ReferenceRT)
        {
            m_VideoSession->CreateDecodeRenderTarget(m_ReferenceRT, *videoProfile.GetProfile(), pVideoFormat->coded_width, pVideoFormat->coded_height);
        }

        if (m_FlowVectorRT)
        {
            m_VideoSession->CreateFlowVectorRenderTarget(m_FlowVectorRT, pVideoFormat->coded_width / 4, pVideoFormat->coded_height / 4);
        }

        m_videoFormat = *pVideoFormat;
        return 1;
    }

    bool Decoder::AllocPictureBuffer(VkPicIf** picIf)
    {
        auto p = new VkPicIf2{};

        p->m_picIdx = m_VideoSession->DPB().PopDecodeSlot();

        *picIf = p;

        return true;
    }

    bool Decoder::DecodePicture(VkParserPictureData* pd)
    {
        bool result = false;

        VkParserDecodePictureInfo decodePictureInfo{};

        vkPicBuffBase* pVkPicBuff = (vkPicBuffBase*)(pd->pCurrPic);

        decodePictureInfo.pictureIndex              = pVkPicBuff->m_picIdx;
        decodePictureInfo.flags.progressiveFrame    = pd->progressive_frame;
        decodePictureInfo.flags.fieldPic            = pd->field_pic_flag;     // 0 = frame picture, 1 = field picture
        decodePictureInfo.flags.repeatFirstField    = pd->repeat_first_field; // For 3:2 pulldown (number of additional fields,
        // 2 = frame doubling, 4 = frame tripling)
        decodePictureInfo.flags.refPic              = pd->ref_pic_flag;       // Frame is a reference frame

        // Mark the first field as unpaired Detect unpaired fields
        if (pd->field_pic_flag) {
            decodePictureInfo.flags.bottomField = pd->bottom_field_flag; // 0 = top field, 1 = bottom field (ignored if
            // field_pic_flag=0)
            decodePictureInfo.flags.secondField = pd->second_field; // Second field of a complementary field pair
            decodePictureInfo.flags.topFieldFirst = pd->top_field_first; // Frame pictures only

            if (!pd->second_field) {
                decodePictureInfo.flags.unpairedField = true; // Incomplete (half) frame.
            }
            else {
                if (decodePictureInfo.flags.unpairedField) {
                    decodePictureInfo.flags.syncToFirstField = true;
                    decodePictureInfo.flags.unpairedField = false;
                }
            }
        }

        decodePictureInfo.frameSyncinfo.unpairedField    = decodePictureInfo.flags.unpairedField;
        decodePictureInfo.frameSyncinfo.syncToFirstField = decodePictureInfo.flags.syncToFirstField;

        return DecodePicture(pd, &decodePictureInfo);
    }

    void Decoder::CmdDecode(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkVideoPictureResourceInfoKHR* pics, VkVideoReferenceSlotInfoKHR* info) const
    {
        auto refCount = pCurrFrameDecParams->numGopReferenceSlots;
        auto range    = pCurrFrameDecParams->bitstreamDataLen;

        CmdList2 cmdList(GetContext());

        cmdList.SetVideoDecodeCmdList();

        cmdList.SetVideoSession(m_VideoSession);

        cmdList.SetQueryPool(m_VideoSession->GetQueryPool());

        cmdList.Begin();

        cmdList.CmdResetQueryPool();

        {
            VkVideoBeginCodingInfoKHR                                beginInfo{};
            beginInfo.sType                                        = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR;
            beginInfo.videoSession                                 = m_VideoSession->Handle();
            beginInfo.videoSessionParameters                       = m_VideoSession->Parameters();
            beginInfo.referenceSlotCount                           = refCount + 1;
            beginInfo.pReferenceSlots                              = info;

            cmdList.CmdBeginVideoCoding(beginInfo);
        }

        static std::once_flag flag;

        std::call_once(flag, [&]() {
            cmdList.CmdControlVideoCoding();
        });

        {
            VkVideoInlineQueryInfoKHR                                queryInfo{};
            queryInfo.sType                                        = VK_STRUCTURE_TYPE_VIDEO_INLINE_QUERY_INFO_KHR;
            queryInfo.queryPool                                    = m_VideoSession->GetQueryPool()->Handle();
            queryInfo.firstQuery                                   = m_VideoSession->DPB().DecodeSlot();
            queryInfo.queryCount                                   = 1;
            queryInfo.pNext                                        = pCurrFrameDecParams->decodeFrameInfo.pNext;

            info[refCount].slotIndex                               = m_VideoSession->DPB().DecodeSlot();

            VkVideoDecodeInfoKHR                                     decodeInfo{};
            decodeInfo.sType                                       = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
            decodeInfo.flags                                       = pCurrFrameDecParams->decodeFrameInfo.flags;
            decodeInfo.srcBuffer                                   = pCurrFrameDecParams->bitstreamData->Handle();
            decodeInfo.srcBufferOffset                             = pCurrFrameDecParams->bitstreamDataOffset;
            decodeInfo.srcBufferRange                              = range;
            decodeInfo.dstPictureResource                          = pics[refCount];
            decodeInfo.pSetupReferenceSlot                         = &info[refCount];
            decodeInfo.referenceSlotCount                          = refCount;
            decodeInfo.pReferenceSlots                             = info;
            decodeInfo.pNext                                       = &queryInfo;

            cmdList.CmdDecodeVideo(decodeInfo);
        }

        cmdList.CmdEndVideoCoding();

        cmdList.End();

        cmdList.SubmitWait();

        assert(m_VideoSession->GetDecodeResult());
    }

    bool Decoder::DisplayPicture(VkPicIf* pPicBuff, int64_t timestamp) const
    {
        auto pic = static_cast<VkPicIf2*>(pPicBuff);

        m_VideoSession->PushDisplaySlot(pic->m_picIdx);

        return true;
    }

    void Decoder::SetDecodeRenderTarget(const SP<RHI::RenderTarget>& renderTarget)
    {
        m_DecodeRT = renderTarget->GetRHIImpl<RenderTarget>();
    }

    void Decoder::SetReferenceRenderTarget(const SP<RHI::RenderTarget>& renderTarget)
    {
        m_ReferenceRT = renderTarget->GetRHIImpl<RenderTarget>();
    }

    void Decoder::SetFlowVectorRenderTarget(const SP<RHI::RenderTarget>& renderTarget)
    {
        m_FlowVectorRT = renderTarget->GetRHIImpl<RenderTarget>();
    }

    void Decoder::PushNextFrameToRenderTarget()
    {
        if (!m_DecodeRT) return;

        if (m_ReferenceRT)
        {
            m_DecodeRT->CopyToRenderTarget(m_ReferenceRT);
        }

        auto slot = m_VideoSession->PopDisplaySlot();

        {
            CmdList2 cmdList(GetContext());

            cmdList.SetGraphicCmdList();

            cmdList.Begin();

            VkImageCopy                                     region{};
            region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
            region.srcSubresource.layerCount              = 1;
            region.srcSubresource.baseArrayLayer          = 0;
            region.srcSubresource.mipLevel                = 0;
            region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
            region.dstSubresource.layerCount              = 1;
            region.dstSubresource.baseArrayLayer          = 0;
            region.dstSubresource.mipLevel                = 0;
            region.extent.width                           = m_codedExtent.width;
            region.extent.height                          = m_codedExtent.height;
            region.extent.depth                           = 1;

            cmdList.CmdTransitionLayout(m_DecodeRT->IHandle(),  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

            cmdList.CmdCopyImage(m_VideoSession->DPB().Handle(slot), m_DecodeRT->Handle(), region);

            region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_1_BIT;
            region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_1_BIT;
            region.extent.width                           = m_codedExtent.width  / 2;
            region.extent.height                          = m_codedExtent.height / 2;

            cmdList.CmdCopyImage(m_VideoSession->DPB().Handle(slot), m_DecodeRT->Handle(), region);

            cmdList.CmdTransitionLayout(m_DecodeRT->IHandle(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

            cmdList.End();

            cmdList.SubmitWait();
        }
    }

    void Decoder::ParserDataChunk(uint8_t* data, uint64_t size)
	{
        size_t consumed = 0;
        bool requiresPartialParsing = false;

        if (data && size)
        {
            ParseVideoStreamData(data, (size_t)size, &consumed, requiresPartialParsing);
        }
        else 
        {
            ParseVideoStreamData(nullptr, 0, &consumed, requiresPartialParsing);

            m_videoStreamsCompleted = true;
        }
	}

	void Decoder::ParseVideoStreamData(const uint8_t* pData, size_t size, size_t *pnVideoBytes, bool doPartialParsing, uint32_t flags, int64_t timestamp)
	{
        VkParserSourceDataPacket packet = { 0 };

        packet.payload            = pData;
        packet.payload_size       = size;
        packet.flags              = flags;
        if (timestamp) 
        {
            packet.flags         |= VK_PARSER_PKT_TIMESTAMP;
        }
        packet.timestamp          = timestamp;

        if (!pData || size == 0) 
        {
            packet.flags         |= VK_PARSER_PKT_ENDOFSTREAM;
        }

        return ParseVideoData(&packet, pnVideoBytes, doPartialParsing);
	}

    void Decoder::ParseVideoData(VkParserSourceDataPacket* pPacket, size_t* pParsedBytes, bool doPartialParsing) const
    {
        VkParserBitstreamPacket pkt{};

        if (pPacket->flags & VK_PARSER_PKT_DISCONTINUITY)
        {
            pkt.bDiscontinuity = true;

            m_Decoder->ParseByteStream(&pkt, pParsedBytes);
        }

        pkt.pByteStream        = pPacket->payload;
        pkt.nDataLength        = pPacket->payload_size;
        pkt.bEOS               = !!(pPacket->flags & VK_PARSER_PKT_ENDOFSTREAM);
        pkt.bEOP               = !!(pPacket->flags & VK_PARSER_PKT_ENDOFPICTURE);
        pkt.bPTSValid          = !!(pPacket->flags & VK_PARSER_PKT_TIMESTAMP);
        pkt.llPTS              = pPacket->timestamp;
        pkt.bPartialParsing    = doPartialParsing;

        m_Decoder->ParseByteStream(&pkt, pParsedBytes);
	}
}

#endif