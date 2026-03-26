#pragma once
#include "Render/Backend/Vulkan/VideoParser/SIMD/SIMD.h"
#include "Render/Backend/Vulkan/VideoParser/PictureBufferBase.h"
#include "VulkanVideoParserIf.h"
#include "Render/Backend/Vulkan/Resource/VideoSession.h"

#include <vulkan/vulkan.h>
#include <atomic>
#include <cassert>
#include <vector>
#include <memory>
#include <functional>

namespace Neptune::Vulkan {

    typedef struct NvVkNalUnit
    {
        int64_t  start_offset;     // Start offset in byte stream buffer
        int64_t  end_offset;       // End offset in byte
        int64_t  get_offset;       // Current read ptr in this NALU
        int32_t  get_zerocnt;      // Zero byte count
        uint32_t get_bfr;          // Bit buffer for reading
        uint32_t get_bfroffs;      // Offset in bit buffer
        uint32_t get_emulcnt;      // Emulation prevention byte count
    } NvVkNalUnit;

    // Presentation information stored with every decoded frame
    typedef struct NvVkPresentationInfo
    {
        VkPicIf* pPicBuf;        // NOTE: May not be valid -> only used to uniquely identify a frame
        int32_t   lNumFields;     // Number of displayed fields (to compute frame duration)
        int32_t   bSkipped;       // true if frame was not decoded (skip display)
        int32_t   bPTSValid;      // Frame has an associated PTS
        int32_t   lPOC;           // Picture Order Count (for initial PTS interpolation)
        int64_t   llPTS;          // Frame presentation time
        int32_t   bDiscontinuity; // Discontinuity before this PTS, do not check for out of order
    } NvVkPresentationInfo;

    class VulkanVideoDecoder : public VulkanVideoDecodeParser, public ContextAccessor
    {
    public:

        enum { MAX_SLICES = 8192 };        // Up to 8K slices per picture
        enum { MAX_DELAY = 32 };           // Maximum frame delay between decode & display
        enum { MAX_QUEUED_PTS = 16 };       // Size of PTS queue
        enum {
            NALU_DISCARD = 0,                // Discard this nal unit
            NALU_SLICE,                    // This NALU contains picture data (keep)
            NALU_UNKNOWN,                  // This NALU type is not supported (callback client)
        };
        typedef enum {
            NV_NO_ERROR = 0,               // No error detected
            NV_NON_COMPLIANT_STREAM        // Stream is not compliant with codec standards
        } NVCodecErrors;

    public:

        VulkanVideoDecoder(
            Context& context, 
            VideoSession& session,
            ClientDelegate& client);

        ~VulkanVideoDecoder() override = default;

        void Initialize(const VkParserInitDecodeParameters* pNvVkp) override;
        bool Deinitialize();
        bool ParseByteStream(const VkParserBitstreamPacket* pck, size_t* pParsedBytes) override;

        template <SIMD_ISA T>
        bool ParseByteStreamSimd(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
        bool ParseByteStreamC(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
#if defined(__x86_64__) || defined (_M_X64)
        bool ParseByteStreamAVX2(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
        bool ParseByteStreamAVX512(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
        bool ParseByteStreamSSSE3(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
#elif defined(__aarch64__) || defined(_M_ARM64)
        bool ParseByteStreamSVE(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
        bool ParseByteStreamNEON(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
#elif defined(__ARM_ARCH_7A__)
        bool ParseByteStreamNEON(const VkParserBitstreamPacket* pck, size_t* pParsedBytes);
#endif
        bool GetDisplayMasteringInfo(VkParserDisplayMasteringInfo*) override { return false; }

    protected:

        virtual void CreatePrivateContext() = 0;                   // Implemented by derived classes
        virtual void InitParser() = 0;                             // Initialize codec-specific parser state
        virtual bool IsPictureBoundary(int32_t rbsp_size) = 0;     // Returns true if the current NAL unit belongs to a new picture
        virtual int32_t  ParseNalUnit() = 0;                       // Must return NALU_DISCARD or NALU_SLICE
        virtual bool BeginPicture(VkParserPictureData* pnvpd) = 0; // Fills in picture data. Return true if picture should be sent to client
        virtual void EndPicture() {}                               // Called after a picture has been decoded
        virtual void EndOfStream() {}                              // Called to reset parser
        virtual void FreeContext() = 0;

    protected:

        std::atomic<int32_t>             m_refCount;
        uint32_t                         m_264SvcEnabled : 1;                  // enabled NVCS_H264_SVC
        uint32_t                         m_outOfBandPictureParameters : 1;     // Enable out of band parameters cb
        uint32_t                         m_initSequenceIsCalled : 1;
        uint32_t                         m_defaultMinBufferSize;             // Minimum default buffer size that the parser is going to allocate
        uint32_t                         m_bufferOffsetAlignment;            // Minimum buffer offset alignment of the bitstream data for each frame
        uint32_t                         m_bufferSizeAlignment;              // Minimum buffer size alignment of the bitstream data for each frame
        VkDeviceSize                     m_bitstreamDataLen;                 // bitstream buffer size
        uint32_t                         m_BitBfr;                           // Bit Buffer for start code parsing
        int32_t                          m_bEmulBytesPresent;                // Startcode emulation prevention bytes are present in the byte stream
        int32_t                          m_bNoStartCodes;                    // No startcode parsing (only rely on the presence of PTS to detect frame boundaries)
        int32_t                          m_bFilterTimestamps;                // Filter input timestamps in case the decoder is sending the DTS instead of the PTS
        int32_t                          m_MaxFrameBuffers;                  // Max frame buffers to keep as reference
        NvVkNalUnit                      m_nalu;                             // Current NAL unit being filled
        size_t                           m_lMinBytesForBoundaryDetection;    // Min number of bytes needed to detect picture boundaries
        int64_t                          m_lClockRate;                       // System Reference Clock Rate
        int64_t                          m_lFrameDuration;                   // Approximate frame duration in units of (1/m_lClockRate) seconds
        int64_t                          m_llExpectedPTS;                    // Expected PTS of the next frame to be displayed
        int64_t                          m_llParsedBytes;                    // Total bytes parsed by the parser
        int64_t                          m_llNaluStartLocation;              // Byte count at the first byte of the current nal unit
        int64_t                          m_llFrameStartLocation;             // Byte count at the first byte of the picture bitstream data buffer
        int32_t                          m_lErrorThreshold;                  // Error threshold (0=strict, 100=ignore errors)
        int32_t                          m_bFirstPTS;                        // Number of frames displayed
        int32_t                          m_lPTSPos;                          // Current write position in PTS queue
        uint32_t                         m_nCallbackEventCount;              // Decode/Display callback count in current packet
        VkParserSequenceInfo             m_PrevSeqInfo;                      // Current sequence info
        VkParserSequenceInfo             m_ExtSeqInfo;                       // External sequence info from system layer
        NvVkPresentationInfo             m_DispInfo[MAX_DELAY];              // Keeps track of display attributes
        struct {
            int32_t                      bPTSValid;                          // Entry is valid
            int64_t                      llPTS;                              // PTS value
            int64_t                      llPTSPos;                           // PTS position in byte stream
            int32_t                      bDiscontinuity;                     // Discontinuity before this PTS, do not check for out of order
        }                                m_PTSQueue[MAX_QUEUED_PTS];
        int32_t                          m_bDiscontinuityReported;           // Dicontinuity reported
        VkParserPictureData              m_VkPictureData;
        int32_t                          m_iTargetLayer;                     // Specific to SVC only
        int32_t                          m_bDecoderInitFailed;               // Set when m_pClient->BeginSequence fails to create the decoder
        int32_t                          m_lCheckPTS;                        // Run the m_bFilterTimestamps for the first few framew to look for out of order PTS
        NVCodecErrors                    m_eError;
        SIMD_ISA                         m_NextStartCode;
        VideoSession&                    m_VideoSession;
        ClientDelegate                   m_Client;

    protected:

        // Byte stream parsing
        template<SIMD_ISA T>
        size_t             next_start_code(const uint8_t* pdatain, size_t datasize, bool& found_start_code);

        void               nal_unit();
        void               init_dbits();
        int32_t            available_bits();
        int32_t            consumed_bits();
        uint32_t           next_bits(uint32_t n);   // NOTE: n must be in the [1..25] range
        void               skip_bits(uint32_t n);   // advance bitstream position
        uint32_t           u(uint32_t n);   // return next n bits, advance bitstream position
        bool               flag() { return (0 != u(1)); }     // returns flag value
        uint32_t           u16_le() { uint32_t tmp = u(8); tmp |= u(8) << 8; return tmp; }
        uint32_t           u24_le() { uint32_t tmp = u16_le(); tmp |= u(8) << 16; return tmp; }
        uint32_t           u32_le() { uint32_t tmp = u16_le(); tmp |= u16_le() << 16; return tmp; }
        uint32_t           ue();
        int32_t            se();
        uint32_t           f(uint32_t n, uint32_t) { return u(n); }
        bool               byte_aligned() const { return ((m_nalu.get_bfroffs & 7) == 0); }
        void               byte_alignment() { while (!byte_aligned()) u(1); }
        void               end_of_picture();
        void               end_of_stream();
        bool               IsSequenceChange(VkParserSequenceInfo* pnvsi);
        int32_t            init_sequence(VkParserSequenceInfo* pnvsi);  // Must be called by derived classes to initialize the sequence
        void               display_picture(VkPicIf* pPicBuf, bool bEvict = true);
        void               rbsp_trailing_bits();
        bool               end() { return m_nalu.get_offset >= m_nalu.end_offset; }
        bool               more_rbsp_data();
        bool               resizeBitstreamBuffer(VkDeviceSize nExtrabytes);
        VkDeviceSize       swapBitstreamBuffer(VkDeviceSize copyCurrBuffOffset, VkDeviceSize copyCurrBuffSize);
    };

}