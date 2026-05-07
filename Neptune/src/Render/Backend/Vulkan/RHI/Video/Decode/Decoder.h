#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/RHI/Decoder.h"
#include "Render/Backend/Vulkan/VideoParser/Decoder/VulkanVideoDecoder.h"
#include "Render/Backend/Vulkan/Resource/VideoSession.h"
#include "Render/Backend/Vulkan/VideoParser/Decoder/VulkanVideoParserParams.h"

#include <queue>

typedef enum {
    VK_PARSER_PKT_ENDOFSTREAM = 0x01, /**< Set when this is the last packet for this stream  */
    VK_PARSER_PKT_TIMESTAMP = 0x02, /**< Timestamp is valid                                */
    VK_PARSER_PKT_DISCONTINUITY = 0x04, /**< Set when a discontinuity has to be signalled      */
    VK_PARSER_PKT_ENDOFPICTURE = 0x08, /**< Set when the packet contains exactly one frame    */
} VkVideopacketflags;

struct VkParserSourceDataPacket {
    uint32_t flags; /** Combination of VK_PARSER_PKT_XXX flags                              */
    size_t payload_size; /** number of bytes in the payload (may be zero if EOS flag is set) */
    const uint8_t* payload; /** Pointer to packet payload data (may be NULL if EOS flag is set) */
    int64_t timestamp; /** Presentation time stamp (10MHz clock), only valid if
                                             VK_PARSER_PKT_TIMESTAMP flag is set                                 */
};

enum { MAX_FRM_CNT = 32 };
enum { HEVC_MAX_DPB_SLOTS = 16 };
enum { AVC_MAX_DPB_SLOTS = 17 };
enum { MAX_REMAPPED_ENTRIES = 20 };

class vkPicBuffBase {};

class DpbSlot {
public:
    bool isInUse() { return (m_reserved || m_inUse); }

    bool isAvailable() { return !isInUse(); }

    bool Invalidate()
    {
        bool wasInUse = isInUse();
        if (m_picBuf) {
            //m_picBuf->Release();
            m_picBuf = NULL;
        }

        m_reserved = m_inUse = false;

        return wasInUse;
    }

    vkPicBuffBase* getPictureResource() { return m_picBuf; }

    vkPicBuffBase* setPictureResource(vkPicBuffBase* picBuf, int32_t age = 0)
    {
        vkPicBuffBase* oldPic = m_picBuf;

        if (picBuf) {
            //picBuf->AddRef();
        }
        m_picBuf = picBuf;

        if (oldPic) {
            //oldPic->Release();
        }

        m_pictureId = age;
        return oldPic;
    }

    void Reserve() { m_reserved = true; }

    void MarkInUse(int32_t age = 0)
    {
        m_pictureId = age;
        m_inUse = true;
    }

    int32_t getAge() { return m_pictureId; }

private:
    int32_t m_pictureId; // PictureID at map time (age)
    vkPicBuffBase* m_picBuf; // Associated resource
    int32_t m_reserved : 1;
    int32_t m_inUse : 1;
};

class DpbSlots {
public:
    DpbSlots(uint32_t dpbMaxSize)
        : m_dpbMaxSize(0)
        , m_slotInUseMask(0)
        , m_dpb(m_dpbMaxSize)
        , m_dpbSlotsAvailable()
    {
        Init(dpbMaxSize, false);
    }

    int32_t Init(uint32_t newDpbMaxSize, bool reconfigure)
    {
        assert(newDpbMaxSize <= MAX_DPB_REF_AND_SETUP_SLOTS);

        if (!reconfigure) {
            Deinit();
        }

        if (reconfigure && (newDpbMaxSize < m_dpbMaxSize)) {
            return m_dpbMaxSize;
        }

        uint32_t oldDpbMaxSize = reconfigure ? m_dpbMaxSize : 0;
        m_dpbMaxSize = newDpbMaxSize;

        m_dpb.resize(m_dpbMaxSize);

        for (uint32_t ndx = oldDpbMaxSize; ndx < m_dpbMaxSize; ndx++) {
            m_dpb[ndx].Invalidate();
        }

        for (uint8_t dpbIndx = oldDpbMaxSize; dpbIndx < m_dpbMaxSize; dpbIndx++) {
            m_dpbSlotsAvailable.push(dpbIndx);
        }

        return m_dpbMaxSize;
    }

    void Deinit()
    {
        for (uint32_t ndx = 0; ndx < m_dpbMaxSize; ndx++) {
            m_dpb[ndx].Invalidate();
        }

        while (!m_dpbSlotsAvailable.empty()) {
            m_dpbSlotsAvailable.pop();
        }

        m_dpbMaxSize = 0;
        m_slotInUseMask = 0;
    }

    ~DpbSlots() { Deinit(); }

    int8_t AllocateSlot()
    {
        if (m_dpbSlotsAvailable.empty()) {
            assert(!"No more DPB slots are available");
            return -1;
        }
        int8_t slot = (int8_t)m_dpbSlotsAvailable.front();
        assert((slot >= 0) && ((uint8_t)slot < m_dpbMaxSize));
        m_slotInUseMask |= (1 << slot);
        m_dpbSlotsAvailable.pop();
        m_dpb[slot].Reserve();
        return slot;
    }

    void FreeSlot(int8_t slot)
    {
        assert((uint8_t)slot < m_dpbMaxSize);
        assert(m_dpb[slot].isInUse());
        assert(m_slotInUseMask & (1 << slot));

        m_dpb[slot].Invalidate();
        m_dpbSlotsAvailable.push(slot);
        m_slotInUseMask &= ~(1 << slot);
    }

    DpbSlot& operator[](uint32_t slot)
    {
        assert(slot < m_dpbMaxSize);
        return m_dpb[slot];
    }

    // Return the remapped index given an external decode render target index
    int8_t GetSlotOfPictureResource(vkPicBuffBase* pPic)
    {
        for (int8_t i = 0; i < (int8_t)m_dpbMaxSize; i++) {
            if ((m_slotInUseMask & (1 << i)) && m_dpb[i].isInUse() && (pPic == m_dpb[i].getPictureResource())) {
                return i;
            }
        }
        return -1; // not found
    }

    void MapPictureResource(vkPicBuffBase* pPic, int32_t dpbSlot,
        int32_t age = 0)
    {
        for (uint32_t slot = 0; slot < m_dpbMaxSize; slot++) {
            if ((uint8_t)slot == dpbSlot) {
                m_dpb[slot].setPictureResource(pPic, age);
            }
            else if (pPic) {
                if (m_dpb[slot].getPictureResource() == pPic) {
                    FreeSlot(slot);
                }
            }
        }
    }

    uint32_t getSlotInUseMask() { return m_slotInUseMask; }

    uint32_t getMaxSize() { return m_dpbMaxSize; }

private:
    uint32_t m_dpbMaxSize;
    uint32_t m_slotInUseMask;
    std::vector<DpbSlot> m_dpb;
    std::queue<uint8_t> m_dpbSlotsAvailable;
};

struct NvVkDecodeFrameDataSlot {
    uint32_t                                            slot;
    VkCommandBuffer                                     commandBuffer;
};

struct PictureResourceInfo {
    VkImage       image;
    VkFormat      imageFormat;
    VkImageLayout currentImageLayout;
    uint32_t      baseArrayLayer;
};

constexpr uint8_t InvalidImageTypeIdx = (uint8_t)-1;

struct ImageSpecsIndex {
    // decodeDpb type always require an image for the current setup DPB
    uint8_t decodeDpb;
    // decodeOut type always require an image.
    // Used with implementation not using DPB coincide and for AV1 film grain
    uint8_t decodeOut;
    // Can be dedicated or virtual equal to filterOut if the filter supports writing to a linear image
    uint8_t linearOut;
    // Virtual only, if FG is enabled for the current frame is equal to decodeOut.
    // AV1 film grain can also be done using the compute filter
    uint8_t filmGrainOut;
    uint8_t filterOut;
    // filterIn specifies the input of the filter, if enabled.
    // It is virtual only - no resource allocation for it. usually assigned to decodeDpb or decodeOut
    uint8_t filterIn;
    // displayOut specifies the output image for the display, if the presentation is enabled.
    // Virtual only - no resource allocation for it. it can be assigned to decodeDpb, decodeOut, linearOut, filterOut
    uint8_t displayOut;
    uint8_t reserved;

    ImageSpecsIndex()
        : decodeDpb(0)
        , decodeOut(InvalidImageTypeIdx)
        , linearOut(InvalidImageTypeIdx)
        , filmGrainOut(InvalidImageTypeIdx)
        , filterOut(InvalidImageTypeIdx)
        , filterIn(InvalidImageTypeIdx)
        , displayOut(0)
        , reserved(InvalidImageTypeIdx) {
    }
};

struct FrameSynchronizationInfo {
    VkFence frameCompleteFence;
    VkSemaphore frameCompleteSemaphore;
    VkSemaphore consumerCompleteSemaphore;
    VkFence frameConsumerDoneFence;
    uint64_t frameConsumerDoneTimelineValue;
    uint64_t decodeCompleteTimelineValue;
    uint64_t filterCompleteTimelineValue;
    VkQueryPool queryPool;
    uint32_t startQueryId;
    uint32_t numQueries;
    ImageSpecsIndex imageSpecsIndex;
    uint32_t hasFrameCompleteSignalFence : 1;
    uint32_t hasFrameConsumerSignalSemaphore : 1;
    uint32_t hasFrameCompleteSignalSemaphore : 1;
    // post processing filter
    uint32_t hasFilterSignalSemaphore : 1;
    uint32_t syncOnFrameCompleteFence : 1;
    uint32_t syncOnFrameConsumerDoneFence : 1;
};

struct ReferencedObjectsInfo {

    // The bitstream Buffer
    const void* pBitstreamData;
    // PPS
    const void* pStdPps;
    // SPS
    const void* pStdSps;
    // VPS
    const void* pStdVps;

    const void* pFilterPoolNode;

    ReferencedObjectsInfo(const void* pBitstreamDataRef,
        const void* pStdPpsRef,
        const void* pStdSpsRef,
        const void* pStdVpsRef = nullptr,
        const void* pFilterPoolNodeRef = nullptr)
        : pBitstreamData(pBitstreamDataRef)
        , pStdPps(pStdPpsRef)
        , pStdSps(pStdSpsRef)
        , pStdVps(pStdVpsRef)
        , pFilterPoolNode(pFilterPoolNodeRef) {
    }
};

struct nvVideoDecodeH264DpbSlotInfo {
    VkVideoDecodeH264DpbSlotInfoKHR dpbSlotInfo;
    StdVideoDecodeH264ReferenceInfo stdReferenceInfo;

    nvVideoDecodeH264DpbSlotInfo()
        : dpbSlotInfo()
        , stdReferenceInfo()
    {
    }

    const VkVideoDecodeH264DpbSlotInfoKHR* Init(int8_t slotIndex)
    {
        assert((slotIndex >= 0) && (slotIndex < (int8_t)MAX_DPB_REF_AND_SETUP_SLOTS));
        dpbSlotInfo.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR;
        dpbSlotInfo.pNext = NULL;
        dpbSlotInfo.pStdReferenceInfo = &stdReferenceInfo;
        return &dpbSlotInfo;
    }

    bool IsReference() const
    {
        return (dpbSlotInfo.pStdReferenceInfo == &stdReferenceInfo);
    }

    operator bool() const { return IsReference(); }
    void Invalidate() { memset(this, 0x00, sizeof(*this)); }
};

struct nvVideoDecodeH265DpbSlotInfo {
    VkVideoDecodeH265DpbSlotInfoKHR dpbSlotInfo;
    StdVideoDecodeH265ReferenceInfo stdReferenceInfo;

    nvVideoDecodeH265DpbSlotInfo()
        : dpbSlotInfo()
        , stdReferenceInfo()
    {
    }

    const VkVideoDecodeH265DpbSlotInfoKHR* Init(int8_t slotIndex)
    {
        assert((slotIndex >= 0) && (slotIndex < (int8_t)MAX_DPB_REF_SLOTS));
        dpbSlotInfo.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_KHR;
        dpbSlotInfo.pNext = NULL;
        dpbSlotInfo.pStdReferenceInfo = &stdReferenceInfo;
        return &dpbSlotInfo;
    }

    bool IsReference() const
    {
        return (dpbSlotInfo.pStdReferenceInfo == &stdReferenceInfo);
    }

    operator bool() const { return IsReference(); }

    void Invalidate() { memset(this, 0x00, sizeof(*this)); }
};

struct nvVideoDecodeAV1DpbSlotInfo
{
    enum {
        // Number of reference frame types (including intra type)
        TOTAL_REFS_PER_FRAME = 8,
    };
    VkVideoDecodeAV1DpbSlotInfoKHR dpbSlotInfo{};
    StdVideoDecodeAV1ReferenceInfo stdReferenceInfo;
    const VkVideoDecodeAV1DpbSlotInfoKHR* Init(int8_t slotIndex)
    {
        assert((slotIndex >= 0) && (slotIndex < (int8_t)TOTAL_REFS_PER_FRAME));
        dpbSlotInfo.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_DPB_SLOT_INFO_KHR;
        dpbSlotInfo.pNext = nullptr;
        dpbSlotInfo.pStdReferenceInfo = &stdReferenceInfo;
        return &dpbSlotInfo;
    }

    void Invalidate() { memset(this, 0x00, sizeof(*this)); }

    // Set the STD data here for AV1.

};

struct nvVideoDecodeVP9DpbSlotInfo
{
    enum {
        // Number of reference frame types (including intra type)
        TOTAL_REFS_PER_FRAME = 8,
    };
    VkExtent2D codedExtent{};

    void Invalidate() { memset(this, 0x00, sizeof(*this)); }

    // Set the STD data here for VP9.

};

// H.264 internal DPB structure
typedef struct dpbH264Entry {
    int8_t dpbSlot;
    // bit0(used_for_reference)=1: top field used for reference,
    // bit1(used_for_reference)=1: bottom field used for reference
    uint32_t used_for_reference : 2;
    uint32_t is_long_term : 1; // 0 = short-term, 1 = long-term
    uint32_t is_non_existing : 1; // 1 = marked as non-existing
    uint32_t is_field_ref : 1; // set if unpaired field or complementary field pair
    union {
        int16_t FieldOrderCnt[2]; // h.264 : 2*32 [top/bottom].
        int32_t PicOrderCnt; // HEVC PicOrderCnt
    };
    union {
        int16_t FrameIdx; // : 16   short-term: FrameNum (16 bits), long-term:
        // LongTermFrameIdx (4 bits)
        int8_t originalDpbIndex; // Original Dpb source Index.
    };
    vkPicBuffBase* m_picBuff; // internal picture reference

    void setReferenceAndTopBottomField(
        bool isReference, bool nonExisting, bool isLongTerm, bool isFieldRef,
        bool topFieldIsReference, bool bottomFieldIsReference, int16_t frameIdx,
        const int16_t fieldOrderCntList[2], vkPicBuffBase* picBuff)
    {
        is_non_existing = nonExisting;
        is_long_term = isLongTerm;
        is_field_ref = isFieldRef;
        if (isReference && isFieldRef) {
            used_for_reference = (bottomFieldIsReference << bottomFieldShift) | (topFieldIsReference << topFieldShift);
        }
        else {
            used_for_reference = isReference ? 3 : 0;
        }

        FrameIdx = frameIdx;

        FieldOrderCnt[0] = fieldOrderCntList[used_for_reference == 2]; // 0: for progressive and top reference; 1: for
        // bottom reference only.
        FieldOrderCnt[1] = fieldOrderCntList[used_for_reference != 1]; // 0: for top reference only;  1: for bottom
        // reference and progressive.

        dpbSlot = -1;
        m_picBuff = picBuff;
    }

    void setReference(bool isLongTerm, int32_t picOrderCnt,
        vkPicBuffBase* picBuff)
    {
        is_non_existing = (picBuff == NULL);
        is_long_term = isLongTerm;
        is_field_ref = false;
        used_for_reference = (picBuff != NULL) ? 3 : 0;

        PicOrderCnt = picOrderCnt;

        dpbSlot = -1;
        m_picBuff = picBuff;
        originalDpbIndex = -1;
    }

    bool isRef() { return (used_for_reference != 0); }

    StdVideoDecodeH264ReferenceInfoFlags getPictureFlag(bool currentPictureIsProgressive)
    {
        StdVideoDecodeH264ReferenceInfoFlags picFlags = StdVideoDecodeH264ReferenceInfoFlags();

        if (used_for_reference) {
            // picFlags.is_reference = true;
        }

        if (is_long_term) {
            picFlags.used_for_long_term_reference = true;
        }
        if (is_non_existing) {
            picFlags.is_non_existing = true;
        }

        if (is_field_ref) {
            // picFlags.field_pic_flag = true;
        }

        if (!currentPictureIsProgressive && (used_for_reference & topFieldMask)) {
            picFlags.top_field_flag = true;
        }
        if (!currentPictureIsProgressive && (used_for_reference & bottomFieldMask)) {
            picFlags.bottom_field_flag = true;
        }

        return picFlags;
    }

    void setH264PictureData(nvVideoDecodeH264DpbSlotInfo* pDpbRefList,
        VkVideoReferenceSlotInfoKHR* pReferenceSlots,
        uint32_t dpbEntryIdx, uint32_t dpbSlotIndex,
        bool currentPictureIsProgressive)
    {
        assert(dpbEntryIdx < AVC_MAX_DPB_SLOTS);
        assert(dpbSlotIndex < AVC_MAX_DPB_SLOTS);

        assert((dpbSlotIndex == (uint32_t)dpbSlot) || is_non_existing);
        pReferenceSlots[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
        pReferenceSlots[dpbEntryIdx].slotIndex = dpbSlotIndex;
        pReferenceSlots[dpbEntryIdx].pNext = pDpbRefList[dpbEntryIdx].Init(dpbSlotIndex);

        StdVideoDecodeH264ReferenceInfo* pRefPicInfo = &pDpbRefList[dpbEntryIdx].stdReferenceInfo;
        pRefPicInfo->FrameNum = FrameIdx;
        pRefPicInfo->flags = getPictureFlag(currentPictureIsProgressive);
        pRefPicInfo->PicOrderCnt[0] = FieldOrderCnt[0];
        pRefPicInfo->PicOrderCnt[1] = FieldOrderCnt[1];
    }

    void setH265PictureData(nvVideoDecodeH265DpbSlotInfo* pDpbSlotInfo,
        VkVideoReferenceSlotInfoKHR* pReferenceSlots,
        uint32_t dpbEntryIdx, uint32_t dpbSlotIndex)
    {
        assert(dpbEntryIdx < HEVC_MAX_DPB_SLOTS);
        assert(dpbSlotIndex < HEVC_MAX_DPB_SLOTS);
        assert(isRef());

        assert((dpbSlotIndex == (uint32_t)dpbSlot) || is_non_existing);
        pReferenceSlots[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
        pReferenceSlots[dpbEntryIdx].slotIndex = dpbSlotIndex;
        pReferenceSlots[dpbEntryIdx].pNext = pDpbSlotInfo[dpbEntryIdx].Init(dpbSlotIndex);

        StdVideoDecodeH265ReferenceInfo* pRefPicInfo = &pDpbSlotInfo[dpbEntryIdx].stdReferenceInfo;
        pRefPicInfo->PicOrderCntVal = PicOrderCnt;
        pRefPicInfo->flags.used_for_long_term_reference = is_long_term;
    }

    void setAV1PictureData(nvVideoDecodeAV1DpbSlotInfo* pDpbSlotInfo,
        VkVideoReferenceSlotInfoKHR* pReferenceSlots,
        uint32_t dpbEntryIdx, uint32_t dpbSlotIndex)
    {
        assert(dpbEntryIdx < STD_VIDEO_AV1_NUM_REF_FRAMES);
        assert(dpbSlotIndex < STD_VIDEO_AV1_NUM_REF_FRAMES);
        assert(isRef());

        assert((dpbSlotIndex == (uint32_t)dpbSlot) || is_non_existing);
        pReferenceSlots[dpbEntryIdx].sType = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR;
        pReferenceSlots[dpbEntryIdx].slotIndex = dpbSlotIndex;
        pReferenceSlots[dpbEntryIdx].pNext = pDpbSlotInfo[dpbEntryIdx].Init(dpbSlotIndex);

        StdVideoDecodeAV1ReferenceInfo* pRefPicInfo = &pDpbSlotInfo[dpbEntryIdx].stdReferenceInfo;
        (void)pRefPicInfo;
#if 0
        // Logical array - maintained by the parser.
        // Vulkan Video parser.cpp -- maintains its own indices.
        // We can use more indices in the parser than the spec. (Ther eis a max of 8 but we can use 16)
        // Reason for single structure for DPB -- the array is passed in the callback (in the proxy of the processor)
        // It checks which references are in use.
        // 2nd Finds which DPB references were assigned before - and reuses indices.
        // The local array maintains the
        pRefPicInfo->flags.disable_frame_end_update_cdf = ;
        pRefPicInfo->flags.segmentation_enabled = ;
        pRefPicInfo->base_q_idx = ;
        pRefPicInfo->frame_type = ;
        pRefPicInfo->primary_ref_frame_slot_index = primary_ref_frame_slot_index;
        pRefPicInfo->flags.used_for_long_term_reference = is_long_term;
#endif
    }

    void setVP9PictureData(nvVideoDecodeVP9DpbSlotInfo* pDpbSlotInfo,
        VkVideoReferenceSlotInfoKHR* pReferenceSlots,
        uint32_t dpbEntryIdx, uint32_t dpbSlotIndex)
    {
        // TODO: VP9 dpb management
        assert(0);
    }

} dpbH264Entry;

namespace Neptune::RHI {

    class RenderTarget;
}

namespace Neptune::Vulkan {

    class RenderTarget;

	class Decoder : public ContextAccessor, public RHI::RHIDecoder::Impl
	{
	public:

		static SP<Decoder> Create(Context& context, void* payload);

	public:

        Decoder(Context& context);
		~Decoder() override = default;

		void ParserDataChunk(uint8_t* data, uint64_t size) override;

        uint32_t GetDecodedPictureCount() override { return m_VideoSession->GetDisplaySlotCount(); }

        void SetDecodeRenderTarget(const SP<RHI::RenderTarget>& renderTarget) override;

        void SetReferenceRenderTarget(const SP<RHI::RenderTarget>& renderTarget) override;

        void SetFlowVectorRenderTarget(const SP<RHI::RenderTarget>& renderTarget) override;

        void PushNextFrameToRenderTarget() override;

        int32_t BeginSequence(const VkParserSequenceInfo* pnvsi);

        bool DecodePicture(VkParserPictureData* pd);

        bool AllocPictureBuffer(VkPicIf** picIf);

        bool DisplayPicture(VkPicIf* pPicBuff, int64_t timestamp) const;

	private:

		void ParseVideoStreamData(const uint8_t* pData, size_t size, size_t *pnVideoBytes, bool doPartialParsing, uint32_t flags = 0, int64_t timestamp = 0);

        void ParseVideoData(VkParserSourceDataPacket* pPacket, size_t* pParsedBytes, bool doPartialParsing) const;

        int32_t StartVideoSequence(VkParserDetectedVideoFormat* pVideoFormat);

    protected:

        virtual bool DecodePicture(VkParserPictureData* pd, VkParserDecodePictureInfo* pDecodePictureInfo) = 0;

        virtual void DecodePictureWithParameters(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkParserDecodePictureInfo* pDecodePictureInfo, const VkParserHevcPictureData* pin, VkPicIf* pic) = 0;

        void CmdDecode(VkParserPerFrameDecodeParameters* pCurrFrameDecParams, VkVideoPictureResourceInfoKHR* pics, VkVideoReferenceSlotInfoKHR* info) const;

    protected:

        uint32_t                    m_videoFrameNum;
        uint32_t                    m_videoStreamsCompleted : 1;
        SP<VulkanVideoDecoder>      m_Decoder = nullptr;
        SP<Resource::VideoSession>  m_VideoSession;
                                    
        uint32_t                    m_maxNumDecodeSurfaces;
        VkParserSequenceInfo        m_nvsi;
        uint32_t                    m_maxNumDpbSlots;
        DpbSlots                    m_dpb;

        VkExtent2D                  m_codedExtent;
        VkParserDetectedVideoFormat m_videoFormat;
        ImageSpecsIndex             m_imageSpecsIndex;
        RenderTarget*               m_DecodeRT;
        RenderTarget*               m_ReferenceRT;
        RenderTarget*               m_FlowVectorRT;
	};
}

#endif