/**
* @file Demuxer.cpp.
* @brief The Demuxer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Demuxer.h"
#include "FFmpeg/Demuxer.h"

namespace Neptune::Video {

	SP<Demuxer> Demuxer::Create()
	{
		NEPTUNE_PROFILE_ZONE

		return CreateSP<FFmpeg::Demuxer>();
	}

}