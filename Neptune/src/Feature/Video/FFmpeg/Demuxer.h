/**
* @file Demuxer.h.
* @brief The Demuxer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Feature/Video/Demuxer.h"

/*extern "C" {
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#ifndef FF_API_OLD_BSF
#include <libavcodec/bsf.h>
#endif
}*/

namespace Neptune::FFmpeg {

	class Demuxer : public Video::Demuxer
	{
	public:

		Demuxer() = default;
		~Demuxer() override = default;

		 void Initialize(const std::filesystem::path& path, VideoOperation op) override;

         Video::Packet DemuxFrame() override;

	private:

		/*AVFormatContext*              m_Fmtc        = nullptr;
        AVIOContext*                  m_Avioc       = nullptr;
        AVPacket*                     m_Pkt         = nullptr;
        AVPacket*                     m_PktFiltered = nullptr;
        AVBSFContext*                 m_Bsfc        = nullptr;
        AVCodecParameters             m_Params;*/

        int                           m_VideoStream;
        int                           m_CodedLumaBitDepth;
        int                           m_CodedChromaBitDepth;
        int                           m_Profile;
        bool                          m_IsStreamDemuxer;
	};
}