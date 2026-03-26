#pragma once
#include "Core/Core.h"
#include <vk_video/vulkan_video_codec_h264std.h>
#include <vk_video/vulkan_video_codec_h265std.h>
#include <vk_video/vulkan_video_codec_av1std.h>
#include <memory>

namespace Neptune::Vulkan {

    class StdVideoPictureParametersSet
    {
    public:

        enum class StdType : uint8_t
        {
            TYPE_H264_SPS = 0,
            TYPE_H264_PPS,
            TYPE_H265_VPS,
            TYPE_H265_SPS,
            TYPE_H265_PPS,
            TYPE_AV1_SPS,

            Count
        };

        enum class ParameterType : uint8_t
        {
            PPS_TYPE = 0,
            SPS_TYPE,
            VPS_TYPE,
            AV1_SPS_TYPE,
            NUM_OF_TYPES,
            INVALID_TYPE,

            Count
        };

        virtual int32_t GetVpsId(bool& isVps) const = 0;
        virtual int32_t GetSpsId(bool& isSps) const = 0;
        virtual int32_t GetPpsId(bool& isPps) const = 0;

        virtual const StdVideoH264SequenceParameterSet* GetStdH264Sps() const { return nullptr; }
        virtual const StdVideoH264PictureParameterSet*  GetStdH264Pps() const { return nullptr; }
        virtual const StdVideoH265VideoParameterSet*    GetStdH265Vps() const { return nullptr; }
        virtual const StdVideoH265SequenceParameterSet* GetStdH265Sps() const { return nullptr; }
        virtual const StdVideoH265PictureParameterSet*  GetStdH265Pps() const { return nullptr; }
        virtual const StdVideoAV1SequenceHeader*        GetStdAV1Sps() const  { return nullptr; }

        StdType       GetStdType()             const { return m_stdType; }
        ParameterType GetParameterType()       const { return m_parameterType; }
        uint32_t      GetUpdateSequenceCount() const { return m_updateSequenceCount; }

    protected:

        StdVideoPictureParametersSet(
            StdType updateType,
            ParameterType itemType,
            uint64_t updateSequenceCount)
            : m_stdType(updateType)
            , m_parameterType(itemType)
            , m_updateSequenceCount((uint32_t)updateSequenceCount)
            , m_parent() 
        {}

        virtual ~StdVideoPictureParametersSet()
        {
            m_parent = nullptr;
        }

    private:
        StdType                                          m_stdType;
        ParameterType                                    m_parameterType;
    protected:
        uint32_t                                         m_updateSequenceCount;
    public:
        SP<StdVideoPictureParametersSet>    m_parent;        // SPS or PPS parent

    };

}