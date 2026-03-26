#include "Pchheader.h"
#include "VulkanVideoDecoder.h"
#include "Render/Backend/Vulkan/VideoParser/STD/nvVulkanVideoUtils.h"
#include <algorithm>
#include <stdarg.h>

namespace Neptune::Vulkan {

    VulkanVideoDecoder::VulkanVideoDecoder(
        Context& context, 
        VideoSession& session, 
        ClientDelegate& client)
        : ContextAccessor(context)
        , m_refCount(0)
        , m_264SvcEnabled(false)
        , m_outOfBandPictureParameters(false)
        , m_initSequenceIsCalled(false)
        , m_defaultMinBufferSize(2 * 1024 * 1024)
        , m_bufferOffsetAlignment(256)
        , m_bufferSizeAlignment(256)
        , m_bitstreamDataLen()
        , m_BitBfr()
        , m_bEmulBytesPresent()
        , m_bNoStartCodes(false)
        , m_bFilterTimestamps(false)
        , m_MaxFrameBuffers()
        , m_nalu{}
        , m_lMinBytesForBoundaryDetection(256)
        , m_lClockRate()
        , m_lFrameDuration()
        , m_llExpectedPTS()
        , m_llParsedBytes()
        , m_llNaluStartLocation()
        , m_llFrameStartLocation()
        , m_lErrorThreshold()
        , m_bFirstPTS()
        , m_lPTSPos()
        , m_nCallbackEventCount()
        , m_PrevSeqInfo{}
        , m_ExtSeqInfo{}
        , m_DispInfo{}
        , m_PTSQueue{}
        , m_bDiscontinuityReported()
        , m_VkPictureData{}
        , m_iTargetLayer(0)
        , m_bDecoderInitFailed()
        , m_lCheckPTS()
        , m_eError(NV_NO_ERROR)
        , m_VideoSession(session)
        , m_Client(client)
    {}

    void VulkanVideoDecoder::Initialize(const VkParserInitDecodeParameters* pParserPictureData)
    {
        Deinitialize();
        m_outOfBandPictureParameters = pParserPictureData->outOfBandPictureParameters;
        m_lClockRate = (pParserPictureData->referenceClockRate > 0) ? pParserPictureData->referenceClockRate : 10000000; // Use 10Mhz as default clock
        m_lErrorThreshold = pParserPictureData->errorThreshold;
        m_bDiscontinuityReported = false;
        m_lFrameDuration = 0;
        m_llExpectedPTS = 0;
        m_bNoStartCodes = false;
        m_bFilterTimestamps = false;
        m_lCheckPTS = 16;
        m_bEmulBytesPresent = false;
        m_bFirstPTS = true;
        if (pParserPictureData->pExternalSeqInfo) {
            m_ExtSeqInfo = *pParserPictureData->pExternalSeqInfo;
        }

        m_bitstreamDataLen = m_VideoSession.Buffer()->Size();

        CreatePrivateContext();
        m_BitBfr = (uint32_t)~0;
        m_MaxFrameBuffers = 0;
        m_bDecoderInitFailed = false;
        m_llParsedBytes = 0;
        m_llNaluStartLocation = 0;
        m_llFrameStartLocation = 0;
        m_lPTSPos = 0;
        InitParser();
        m_nalu = {};
        m_NextStartCode = GetSIMD();
    }

    bool VulkanVideoDecoder::Deinitialize()
    {
        FreeContext();
        return true;
    }

    void VulkanVideoDecoder::init_dbits()
    {
        m_nalu.get_offset = m_nalu.start_offset + ((m_bNoStartCodes) ? 0 : 3);  // Skip over start_code_prefix
        m_nalu.get_zerocnt = 0;
        m_nalu.get_emulcnt = 0;
        m_nalu.get_bfr = 0;
        // prime bit buffer
        m_nalu.get_bfroffs = 32;
        skip_bits(0);
    }

    int32_t VulkanVideoDecoder::available_bits()
    {
        // end_offset=566 - get_offset=568 for example are values seen in the debugger, 
        // causing an unsigned integer overflow below since get_btroffs is a uint32 
        // while end_offset and get_offset are int64 explicitly casted to int32, 
        // which then gets implicitly casted to a unint32. This code could use a review 
        // from the original authors about the intentions here. The early return is 
        // to avoid the sanitizer violation and appears semantically correct.
        if ((m_nalu.end_offset - m_nalu.get_offset) < 0)
        {
            return 0;
        }
        assert((m_nalu.end_offset - m_nalu.get_offset) < std::numeric_limits<int32_t>::max());
        return (int32_t)(m_nalu.end_offset - m_nalu.get_offset) * 8 + (32 - m_nalu.get_bfroffs);
    }

    int32_t VulkanVideoDecoder::consumed_bits()
    {
        assert((m_nalu.get_offset - m_nalu.start_offset - m_nalu.get_emulcnt) < std::numeric_limits<int32_t>::max());
        return (int32_t)(m_nalu.get_offset - m_nalu.start_offset - m_nalu.get_emulcnt) * 8 - (32 - m_nalu.get_bfroffs);
    }

    uint32_t VulkanVideoDecoder::next_bits(uint32_t n)
    {
        return (m_nalu.get_bfr << m_nalu.get_bfroffs) >> (32 - n);
    }


    void VulkanVideoDecoder::skip_bits(uint32_t n)
    {
        m_nalu.get_bfroffs += n;
        while (m_nalu.get_bfroffs >= 8)
        {
            m_nalu.get_bfr <<= 8;
            if (m_nalu.get_offset < m_nalu.end_offset)
            {
                VkDeviceSize c = m_VideoSession.Buffer()->Read(m_nalu.get_offset++);
                if (m_bEmulBytesPresent)
                {
                    // detect / discard emulation_prevention_three_byte
                    if (m_nalu.get_zerocnt == 2)
                    {
                        if (c == 3)
                        {
                            m_nalu.get_zerocnt = 0;
                            c = (m_nalu.get_offset < m_nalu.end_offset) ? m_VideoSession.Buffer()->Read(m_nalu.get_offset) : 0;
                            m_nalu.get_offset++;
                            m_nalu.get_emulcnt++;
                        }
                    }
                    if (c != 0)
                        m_nalu.get_zerocnt = 0;
                    else
                        m_nalu.get_zerocnt += (m_nalu.get_zerocnt < 2);
                }
                m_nalu.get_bfr |= c;
            }
            else
            {
                m_nalu.get_offset++;
            }
            m_nalu.get_bfroffs -= 8;
        }
    }

    void VulkanVideoDecoder::rbsp_trailing_bits()
    {
        f(1, 1); // rbsp_stop_one_bit
        while (!byte_aligned())
            f(1, 0); // rbsp_alignment_zero_bit
    }

    bool VulkanVideoDecoder::more_rbsp_data()
    {
        // If the NAL unit contains any non-zero bits past the next bit we have more RBSP data.
        // These non-zero bits may either already be in bfr (first check)
        // or may not have been read yet (second check).
        // Note that the assumption that end() == false implies that there are more unread
        // non-zero bits is invalid for CABAC slices (because of cabac_zero_word). This is not
        // a problem because more_rbsp_data is not used in CABAC slices. 
        return (m_nalu.get_bfr << (m_nalu.get_bfroffs + 1)) != 0 || !end();
    }

    uint32_t VulkanVideoDecoder::u(uint32_t n)
    {
        uint32_t bits = 0;

        if (n > 0)
        {
            if (n + m_nalu.get_bfroffs <= 32)
            {
                bits = next_bits(n);
                skip_bits(n);
            }
            else
            {
                // n == 26..32
                bits = next_bits(n - 25) << 25;
                skip_bits(n - 25);
                bits |= next_bits(25);
                skip_bits(25);
            }
        }
        return bits;
    }


    // 9.1
    uint32_t VulkanVideoDecoder::ue()
    {
        int leadingZeroBits, b, codeNum;

        leadingZeroBits = -1;
        for (b = 0; (!b) && (leadingZeroBits < 32); leadingZeroBits++)
            b = u(1);

        codeNum = 0;
        if (leadingZeroBits < 32)
        {
            codeNum = (1 << leadingZeroBits) - 1 + u(leadingZeroBits);
        }
        else
        {
            codeNum = 0xffffffff + u(leadingZeroBits);
        }
        return codeNum;
    }


    // 9.1.1
    int32_t VulkanVideoDecoder::se()
    {
        uint32_t eg = ue();  // Table 9-3
        int32_t codeNum;

        if (eg & 1)
            codeNum = (int32_t)((eg >> 1) + 1);
        else
            codeNum = -(int32_t)(eg >> 1);
        return codeNum;
    }

    bool VulkanVideoDecoder::resizeBitstreamBuffer(VkDeviceSize extraBytes)
    {
        auto buffer = m_VideoSession.Buffer();
        auto size   = buffer->Size();
        auto ptr    = buffer->HostData();

        m_VideoSession.CreateBuffer(size + std::max<VkDeviceSize>(extraBytes, (2 * 1024 * 1024)));

        m_VideoSession.Buffer()->WriteToBuffer(ptr, size);

        m_bitstreamDataLen = m_VideoSession.Buffer()->Size();

        return true;
    }

    VkDeviceSize VulkanVideoDecoder::swapBitstreamBuffer(VkDeviceSize copyCurrBuffOffset, VkDeviceSize copyCurrBuffSize)
    {
        auto buffer = m_VideoSession.Buffer();
        auto size   = buffer->Size();
        auto ptr    = buffer->HostData() + copyCurrBuffOffset;

        m_VideoSession.CreateBuffer();

        m_VideoSession.Buffer()->WriteToBuffer(ptr, copyCurrBuffSize);

        return m_VideoSession.Buffer()->Size();
    }

    bool VulkanVideoDecoder::ParseByteStream(const VkParserBitstreamPacket* pck, size_t* pParsedBytes)
    {
#if defined(__x86_64__) || defined (_M_X64)
        if (m_NextStartCode == SIMD_ISA::AVX512)
        {
            return ParseByteStreamAVX512(pck, pParsedBytes);
        }
        else if (m_NextStartCode == SIMD_ISA::AVX2)
        {
            return ParseByteStreamAVX2(pck, pParsedBytes);
        }
        else if (m_NextStartCode == SIMD_ISA::SSSE3)
        {
            return ParseByteStreamSSSE3(pck, pParsedBytes);
        }
        else
#elif defined(__aarch64__) || defined(__ARM_ARCH_7A__) || defined(_M_ARM64)
#if defined(__aarch64__)
        if (m_NextStartCode == SIMD_ISA::SVE)
        {
            return ParseByteStreamSVE(pck, pParsedBytes);
        }
        else
#endif //__aarch64__
#if defined(__ARM_NEON)
            if (m_NextStartCode == SIMD_ISA::NEON)
            {
                return ParseByteStreamNEON(pck, pParsedBytes);
            }
            else
#endif // __ARM_NEON
#endif
            {
                return ParseByteStreamC(pck, pParsedBytes);
            }
    }

    void VulkanVideoDecoder::nal_unit()
    {
        if (m_nalu.end_offset - m_nalu.start_offset > 3 && m_VideoSession.Buffer()->HasSliceStartCodeAtOffset(m_nalu.start_offset))
        {
            int nal_type;
            init_dbits();
            if (IsPictureBoundary(available_bits() >> 3))
            {
                if (m_nalu.start_offset > 0)
                {
                    end_of_picture();

                    // This swap will copy to the new buffer most of the time.
                    m_bitstreamDataLen = swapBitstreamBuffer(m_nalu.start_offset, m_nalu.end_offset - m_nalu.start_offset);
                    m_nalu.end_offset -= m_nalu.start_offset;
                    m_nalu.start_offset = 0;
                    m_VideoSession.Buffer()->ResetStreamMarkers();
                    m_llNaluStartLocation = m_llParsedBytes - m_nalu.end_offset;
                }
            }
            init_dbits();
            nal_type = ParseNalUnit();
            switch (nal_type)
            {
            case NALU_SLICE:
                if (m_VideoSession.Buffer()->GetStreamMarkersCount() < MAX_SLICES)
                {
                    if (m_VideoSession.Buffer()->GetStreamMarkersCount() == 0) {
                        m_llFrameStartLocation = m_llNaluStartLocation;
                    }
                    assert(m_nalu.start_offset < std::numeric_limits<int32_t>::max());
                    m_VideoSession.Buffer()->AddStreamMarker((uint32_t)m_nalu.start_offset);
                }
                break;
                //case NALU_DISCARD:
            default:
                if (nal_type == NALU_UNKNOWN)
                {
                    // Called client for handling unsupported NALUs (or user data)
                    const uint8_t* bitstreamDataPtr = m_VideoSession.Buffer()->HostData();
                    int64_t cbData = (m_nalu.end_offset - m_nalu.start_offset - 3);
                    assert((uint64_t)cbData < (uint64_t)std::numeric_limits<size_t>::max());
                    //m_pClient->UnhandledNALU(bitstreamDataPtr + m_nalu.start_offset + 3, (size_t)cbData);
                }
                m_nalu.end_offset = m_nalu.start_offset;
            }
        }
        else
        {
            // Discard invalid NALU
            m_nalu.end_offset = m_nalu.start_offset;
        }
        m_nalu.start_offset = m_nalu.end_offset;
    }

    bool VulkanVideoDecoder::IsSequenceChange(VkParserSequenceInfo* pnvsi)
    {
        if (memcmp(pnvsi, &m_PrevSeqInfo, sizeof(VkParserSequenceInfo)))
            return true;
    }

    int VulkanVideoDecoder::init_sequence(VkParserSequenceInfo* pnvsi)
    {
        // Detect sequence info changes
        if (memcmp(pnvsi, &m_PrevSeqInfo, sizeof(VkParserSequenceInfo)))
        {
            uint32_t lNumerator, lDenominator;
            memcpy(&m_PrevSeqInfo, pnvsi, sizeof(VkParserSequenceInfo));
            m_MaxFrameBuffers = m_Client.BeginSequence(&m_PrevSeqInfo);
            if (!m_MaxFrameBuffers)
            {
                m_bDecoderInitFailed = true;
                return 0;
            }
            lNumerator = NV_FRAME_RATE_NUM(pnvsi->frameRate);
            lDenominator = NV_FRAME_RATE_DEN(pnvsi->frameRate);
            // Determine frame duration
            if ((m_lClockRate > 0) && (lNumerator > 0) && (lDenominator > 0))
            {
                m_lFrameDuration = (int32_t)((uint64_t)lDenominator * m_lClockRate / (uint32_t)lNumerator);
            }
            else if (m_lFrameDuration <= 0)
            {
                // Default to 30Hz for timestamp interpolation
                m_lFrameDuration  = m_lClockRate / 30;
            }
        }

        return m_MaxFrameBuffers;
    }

    void VulkanVideoDecoder::end_of_picture()
    {
        if ((m_nalu.end_offset > 3) && (m_VideoSession.Buffer()->GetStreamMarkersCount() > 0))
        {
            assert(!m_264SvcEnabled);
            m_VkPictureData = {};
            m_VkPictureData.bitstreamDataOffset = 0;
            m_VkPictureData.firstSliceIndex = 0;
            m_VkPictureData.bitstreamData = m_VideoSession.Buffer().get();
            assert((uint64_t)m_nalu.start_offset < (uint64_t)std::numeric_limits<size_t>::max());
            m_VkPictureData.bitstreamDataLen = (size_t)m_nalu.start_offset;
            m_VkPictureData.numSlices = m_VideoSession.Buffer()->GetStreamMarkersCount();
            if (BeginPicture(&m_VkPictureData))
            {
                if ((&m_VkPictureData + m_iTargetLayer)->pCurrPic)
                {
                    int32_t lDisp = 0;

                    // Find an entry in m_DispInfo
                    for (int32_t i = 0; i < MAX_DELAY; i++)
                    {
                        if (m_DispInfo[i].pPicBuf == (&m_VkPictureData + m_iTargetLayer)->pCurrPic)
                        {
                            lDisp = i;
                            break;
                        }
                        if ((m_DispInfo[i].pPicBuf == NULL)
                            || ((m_DispInfo[lDisp].pPicBuf != NULL) && (m_DispInfo[i].llPTS - m_DispInfo[lDisp].llPTS < 0)))
                            lDisp = i;
                    }
                    m_DispInfo[lDisp].pPicBuf = (&m_VkPictureData + m_iTargetLayer)->pCurrPic;
                    m_DispInfo[lDisp].bSkipped = false;
                    m_DispInfo[lDisp].bDiscontinuity = false;
                    m_DispInfo[lDisp].lPOC = (&m_VkPictureData + m_iTargetLayer)->picture_order_count;
                    if (((&m_VkPictureData + m_iTargetLayer)->field_pic_flag) && (!(&m_VkPictureData + m_iTargetLayer)->second_field))
                        m_DispInfo[lDisp].lNumFields = 1;
                    else
                        m_DispInfo[lDisp].lNumFields = 2 + (&m_VkPictureData + m_iTargetLayer)->repeat_first_field;
                    if ((!(&m_VkPictureData + m_iTargetLayer)->second_field) // Ignore PTS of second field if we already got a PTS for the 1st field
                        || (!m_DispInfo[lDisp].bPTSValid))
                    {
                        // Find a PTS in the list
                        unsigned int ndx = m_lPTSPos;
                        m_DispInfo[lDisp].bPTSValid = false;
                        m_DispInfo[lDisp].llPTS = m_llExpectedPTS; // Will be updated later on
                        for (int k = 0; k < MAX_QUEUED_PTS; k++)
                        {
                            if ((m_PTSQueue[ndx].bPTSValid) && (m_PTSQueue[ndx].llPTSPos - m_llFrameStartLocation <= (m_bNoStartCodes ? 0 : 3)))
                            {
                                m_DispInfo[lDisp].bPTSValid = true;
                                m_DispInfo[lDisp].llPTS = m_PTSQueue[ndx].llPTS;
                                m_DispInfo[lDisp].bDiscontinuity = m_PTSQueue[ndx].bDiscontinuity;
                                m_PTSQueue[ndx].bPTSValid = false;
                            }
                            ndx = (ndx + 1) % MAX_QUEUED_PTS;
                        }
                    }
                    // Client callback
                    if (!m_Client.DecodePicture(&m_VkPictureData))
                    {
                        m_DispInfo[lDisp].bSkipped = true;
                    }
                    else
                    {
                        m_nCallbackEventCount++;
                    }
                }
                // Call back codec for post-decode event (display the decoded frame)
                EndPicture();
            }
        }
    }

    void VulkanVideoDecoder::display_picture(VkPicIf* pPicBuf, bool bEvict)
    {
        int32_t i, lDisp = -1;

        for (i = 0; i < MAX_DELAY; i++) {
            if (m_DispInfo[i].pPicBuf == pPicBuf)
            {
                lDisp = i;
                break;
            }
        }

        if (lDisp >= 0) {

            int64_t llPTS;
            if (m_DispInfo[lDisp].bPTSValid) {

                llPTS = m_DispInfo[lDisp].llPTS;
                // If filtering timestamps, look for the earliest PTS and swap with the current one so that the output
                // timestamps are always increasing (in case we're incorrectly getting the DTS instead of the PTS)
                if (m_bFilterTimestamps || (m_lCheckPTS && !m_DispInfo[lDisp].bDiscontinuity)) {

                    int32_t lEarliest = lDisp;
                    for (i = 0; i < MAX_DELAY; i++) {

                        if ((m_DispInfo[i].bPTSValid) && (m_DispInfo[i].pPicBuf) && (m_DispInfo[i].llPTS - m_DispInfo[lEarliest].llPTS < 0)) {
                            lEarliest = i;
                        }
                    }
                    if (lEarliest != lDisp) {
                        if (m_lCheckPTS) {
                            m_bFilterTimestamps = true;
                        }
                        llPTS = m_DispInfo[lEarliest].llPTS;
                        m_DispInfo[lEarliest].llPTS = m_DispInfo[lDisp].llPTS;
                        m_DispInfo[lDisp].llPTS = llPTS;
                    }
                    if (m_lCheckPTS) {
                        m_lCheckPTS--;
                    }
                }

            }
            else {

                llPTS = m_llExpectedPTS;
                if (m_bFirstPTS) {
                    // The frame with the first timestamp has not been displayed yet: try to guess
                    // using the difference in POC value if available
                    for (i = 0; i < MAX_DELAY; i++) {
                        if ((m_DispInfo[i].pPicBuf) && (m_DispInfo[i].bPTSValid)) {
                            int lPOCDiff = m_DispInfo[i].lPOC - m_DispInfo[lDisp].lPOC;
                            if (lPOCDiff < m_DispInfo[lDisp].lNumFields)
                                lPOCDiff = m_DispInfo[lDisp].lNumFields;
                            llPTS = m_DispInfo[i].llPTS - ((lPOCDiff * m_lFrameDuration) >> 1);
                            break;
                        }
                    }
                }
            }

            if (!m_DispInfo[lDisp].bSkipped) {

                m_Client.DisplayPicture(pPicBuf, llPTS);
                m_nCallbackEventCount++;
            }

            if (bEvict) {
                m_DispInfo[lDisp].pPicBuf = NULL;
            }
            m_llExpectedPTS = llPTS + (((uint32_t)m_lFrameDuration * (uint32_t)m_DispInfo[lDisp].lNumFields) >> 1);
            m_bFirstPTS = false;

        }
    }

    void VulkanVideoDecoder::end_of_stream()
    {
        EndOfStream();
        // Reset common parser state
        memset(&m_nalu, 0, sizeof(m_nalu));
        memset(&m_PrevSeqInfo, 0, sizeof(m_PrevSeqInfo));
        memset(&m_PTSQueue, 0, sizeof(m_PTSQueue));
        m_BitBfr = (uint32_t)~0;
        m_llParsedBytes = 0;
        m_llNaluStartLocation = 0;
        m_llFrameStartLocation = 0;
        m_lFrameDuration = 0;
        m_llExpectedPTS = 0;
        m_bFirstPTS = true;
        m_lPTSPos = 0;
        for (int i = 0; i < MAX_DELAY; i++)
        {
            m_DispInfo[i].pPicBuf = NULL;
            m_DispInfo[i].bPTSValid = false;
        }
    }

}