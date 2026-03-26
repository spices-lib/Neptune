#pragma once
#include "Render/Backend/Vulkan/Resource/DecodeBuffer.h"
#include <assert.h>
#include <atomic>

static const uint32_t topFieldShift = 0;
static const uint32_t topFieldMask = (1 << topFieldShift);
static const uint32_t bottomFieldShift = 1;
static const uint32_t bottomFieldMask = (1 << bottomFieldShift);
static const uint32_t fieldIsReferenceMask = (topFieldMask | bottomFieldMask);

constexpr uint32_t MAX_DPB_REF_SLOTS = 16;
constexpr uint32_t MAX_DPB_REF_AND_SETUP_SLOTS = MAX_DPB_REF_SLOTS + 1;

namespace Neptune::Vulkan {

    typedef int64_t VkVideotimestamp;

    struct VkParserSourceDataPacket;
    struct VkParserDetectedVideoFormat;
    class StdVideoPictureParametersSet;

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

    struct nvVideoH264PicParameters {
        enum { MAX_REF_PICTURES_LIST_ENTRIES = 16 };

        StdVideoDecodeH264PictureInfo stdPictureInfo;
        VkVideoDecodeH264PictureInfoKHR pictureInfo;
        VkVideoDecodeH264SessionParametersAddInfoKHR pictureParameters;
        nvVideoDecodeH264DpbSlotInfo currentDpbSlotInfo;
        nvVideoDecodeH264DpbSlotInfo dpbRefList[MAX_REF_PICTURES_LIST_ENTRIES];
    };

    struct nvVideoH265PicParameters {
        enum { MAX_REF_PICTURES_LIST_ENTRIES = 16 };

        StdVideoDecodeH265PictureInfo stdPictureInfo;
        VkVideoDecodeH265PictureInfoKHR pictureInfo;
        VkVideoDecodeH265SessionParametersAddInfoKHR pictureParameters;
        nvVideoDecodeH265DpbSlotInfo dpbRefList[MAX_REF_PICTURES_LIST_ENTRIES];
    };

    struct nvVideoAV1PicParameters {
        // Maximum number of tiles specified by any defined level
        uint32_t tileOffsets[256];
        uint32_t tileSizes[256];
        uint16_t MiColStarts[64];
        uint16_t MiRowStarts[64];
        uint16_t width_in_sbs_minus_1[64];
        uint16_t height_in_sbs_minus_1[64];
        StdVideoDecodeAV1PictureInfo stdPictureInfo; // memory for the pointer in pictureInfo
        VkVideoDecodeAV1PictureInfoKHR pictureInfo;
        VkVideoDecodeAV1SessionParametersCreateInfoKHR pictureParameters;
        nvVideoDecodeAV1DpbSlotInfo dpbRefList[nvVideoDecodeAV1DpbSlotInfo::TOTAL_REFS_PER_FRAME + 1];
    };

    struct nvVideoVP9PicParameters {
        StdVideoDecodeVP9PictureInfo stdPictureInfo;
        StdVideoVP9ColorConfig stdColorConfig;
        StdVideoVP9Segmentation stdSegment;
        StdVideoVP9LoopFilter stdLoopFilter;
        VkVideoDecodeVP9PictureInfoKHR vkPictureInfo{ VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_PICTURE_INFO_KHR, nullptr, &stdPictureInfo };
        nvVideoDecodeVP9DpbSlotInfo dpbRefList[nvVideoDecodeVP9DpbSlotInfo::TOTAL_REFS_PER_FRAME + 1];
    };

    struct VkParserPerFrameDecodeParameters {
        enum {
            MAX_DPB_REF_SLOTS = 16,                               // max 16 reference pictures.
            MAX_DPB_REF_AND_SETUP_SLOTS = MAX_DPB_REF_SLOTS + 1,  // plus 1 for the current picture (h.264 only)
        };
        int currPicIdx; /** Output index of the current picture                       */

        // VPS
        const StdVideoPictureParametersSet* pStdVps;
        // SPS
        const StdVideoPictureParametersSet* pStdSps;
        // PPS
        const StdVideoPictureParametersSet* pStdPps;

        // inlined picture parameters that should be inserted to VkVideoBeginCodingInfo
        const void* beginCodingInfoPictureParametersExt;
        uint32_t useInlinedPictureParameters : 1;
        // Bitstream data
        uint32_t firstSliceIndex;
        uint32_t numSlices;
        size_t bitstreamDataOffset;      // bitstream data offset in bitstreamData buffer
        size_t bitstreamDataLen;         // Number of bytes in bitstream data buffer
        DecodeBuffer* bitstreamData;  // bitstream data for this picture (slice-layer)
        VkVideoDecodeInfoKHR decodeFrameInfo;
        VkVideoPictureResourceInfoKHR dpbSetupPictureResource;
        uint32_t numGopReferenceSlots;
        int8_t pGopReferenceImagesIndexes[MAX_DPB_REF_AND_SETUP_SLOTS];
        VkVideoPictureResourceInfoKHR pictureResources[MAX_DPB_REF_AND_SETUP_SLOTS];
    };

    struct VkParserFrameSyncinfo {
        uint32_t unpairedField : 1;     // Generate a semaphore reference, do not return the semaphore.
        uint32_t syncToFirstField : 1;  // Use the semaphore from the unpared field to wait on.
        void* pDebugInterface;
    };

    union VkParserFieldFlags {
        struct {
            uint32_t progressiveFrame : 1;  // Frame is progressive
            uint32_t fieldPic : 1;          // 0 = frame picture, 1 = field picture
            uint32_t bottomField : 1;       // 0 = top field, 1 = bottom field (ignored if field_pic_flag=0)
            uint32_t secondField : 1;       // Second field of a complementary field pair
            uint32_t topFieldFirst : 1;     // Frame pictures only
            uint32_t unpairedField : 1;     // Incomplete (half) frame.
            uint32_t syncFirstReady : 1;    // Synchronize the second field to the first one.
            uint32_t syncToFirstField : 1;  // Synchronize the second field to the first one.
            uint32_t repeatFirstField : 3;  // For 3:2 pulldown (number of additional fields, 2 = frame doubling, 4 = frame tripling)
            uint32_t refPic : 1;            // Frame is a reference frame
            uint32_t applyFilmGrain : 1;    // Valid for AV1 only
        };
        uint32_t fieldFlags;
    };

    struct VkParserDecodePictureInfo {
        int32_t displayWidth;
        int32_t displayHeight;
        int32_t pictureIndex;      // Index of the current picture
        uint32_t imageLayerIndex;  // The layer of a multi-layered images. Always "0" for single layered images
        VkParserFieldFlags flags;
        uint64_t decodePicCount;
        VkVideotimestamp timestamp;  // decode time
        VkParserFrameSyncinfo frameSyncinfo;
        uint16_t viewId;  // HEVC nuh_layer_id & from pictureInfoH264->ext.mvcext.view_id
    };

    struct VulkanVideoDisplayPictureInfo {
        VkVideotimestamp timestamp;  // Presentation time stamp
    };

    struct VkParserDetectedVideoFormat {
        VkVideoCodecOperationFlagBitsKHR codec;  // Compression format
        VkVideoComponentBitDepthFlagsKHR lumaBitDepth;
        VkVideoComponentBitDepthFlagsKHR chromaBitDepth;
        VkVideoChromaSubsamplingFlagBitsKHR chromaSubsampling;
        /**
         * OUT: frame rate = numerator / denominator (for example: 30000/1001)
         */
        struct {
            /** frame rate numerator   (0 = unspecified or variable frame rate) */
            uint32_t numerator;
            /** frame rate denominator (0 = unspecified or variable frame rate) */
            uint32_t denominator;
        } frame_rate;
        uint8_t
            sequenceUpdate : 1; /** if true, this is a sequence update and not the first time StartVideoSequence is being called. **/
        uint8_t sequenceReconfigureFormat : 1;      /** if true, this is a sequence update for the video format. **/
        uint8_t sequenceReconfigureCodedExtent : 1; /** if true, this is a sequence update for the video coded extent. **/
        uint8_t progressive_sequence : 1;           /** false = interlaced, true = progressive  */
        uint8_t bit_depth_luma_minus8;              /** high bit depth luma. E.g, 2 for 10-bitdepth, 4 for 12-bitdepth   */
        uint8_t bit_depth_chroma_minus8;            /** high bit depth chroma. E.g, 2 for 10-bitdepth, 4 for 12-bitdepth */
        uint8_t reserved1;                          /**< Reserved for future use                                               */
        uint32_t coded_width;                       /** coded frame width in pixels                                      */
        uint32_t coded_height;                      /** coded frame height in pixels                                     */
        /**
         * area of the frame that should be displayed
         * typical example:
         * coded_width = 1920, coded_height = 1088
         * display_area = { 0,0,1920,1080 }
         */
        struct {
            int32_t left;   /** left position of display rect    */
            int32_t top;    /** top position of display rect     */
            int32_t right;  /** right position of display rect   */
            int32_t bottom; /** bottom position of display rect  */
        } display_area;
        uint32_t max_session_width;
        uint32_t max_session_height;
        uint32_t bitrate; /** video bitrate (bps, 0=unknown)   */
        /**
         * OUT: Display Aspect Ratio = x:y (4:3, 16:9, etc)
         */
        struct {
            int32_t x;
            int32_t y;
        } display_aspect_ratio;

        uint32_t minNumDecodeSurfaces;  // Minimum number of decode surfaces for correct decoding (NumRefFrames + 2;)
        uint32_t maxNumDpbSlots;        // Can't be more than 16 + 1

        /**
         * Video Signal Description
         * Refer section E.2.1 (VUI parameters semantics) of H264 spec file
         */
        struct {
            uint8_t video_format : 3;          /** 0-Component, 1-PAL, 2-NTSC, 3-SECAM, 4-MAC, 5-Unspecified     */
            uint8_t video_full_range_flag : 1; /** indicates the black level and luma and chroma range           */
            uint8_t reserved_zero_bits : 4;    /**< Reserved bits                                                      */
            uint8_t color_primaries;           /** chromaticity coordinates of source primaries                  */
            uint8_t transfer_characteristics;  /** opto-electronic transfer characteristic of the source picture */
            uint8_t matrix_coefficients;       /** used in deriving luma and chroma signals from RGB primaries   */
        } video_signal_description;
        uint32_t seqhdr_data_length; /** Additional bytes following (NVVIDEOFORMATEX)                  */
        uint32_t codecProfile;
        bool filmGrainUsed;
    };

    typedef enum {
        VK_PARSER_PKT_ENDOFSTREAM = 0x01,   /**< Set when this is the last packet for this stream  */
        VK_PARSER_PKT_TIMESTAMP = 0x02,     /**< Timestamp is valid                                */
        VK_PARSER_PKT_DISCONTINUITY = 0x04, /**< Set when a discontinuity has to be signalled      */
        VK_PARSER_PKT_ENDOFPICTURE = 0x08,  /**< Set when the packet contains exactly one frame    */
    } VkVideopacketflags;

    struct VkParserSourceDataPacket {
        uint32_t flags;             /** Combination of VK_PARSER_PKT_XXX flags                              */
        size_t payload_size;        /** number of bytes in the payload (may be zero if EOS flag is set) */
        const uint8_t* payload;     /** Pointer to packet payload data (may be NULL if EOS flag is set) */
        VkVideotimestamp timestamp; /** Presentation time stamp (10MHz clock), only valid if
                                                 VK_PARSER_PKT_TIMESTAMP flag is set                                 */
    };

}