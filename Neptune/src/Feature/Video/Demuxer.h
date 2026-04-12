/**
* @file Demuxer.h.
* @brief The Demuxer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "VideoOperation.h"

#include <filesystem>

namespace Neptune::Video {

	/**
	* @brief DemuxFrame Data Packet.
	*/
	struct Packet
	{
		uint8_t* data = nullptr;
		uint64_t size = 0;
	};

	/**
	* @brief Video Demuxer Class.
	*/
	class Demuxer
	{
	public:

		static SP<Demuxer> Create();

	public:

		/**
		* @brief Constructor Function.
		*/
		Demuxer() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Demuxer() = default;

		/**
		* @brief Initialize demuxer context.
		* 
		* @param[in] path Video FilePath.
		* @param[in] op VideoOperation.
		*/
		virtual void Initialize(const std::filesystem::path& path, VideoOperation op) = 0;

		/**
		* @brief Demux Frame.
		*
		* @return Returns Frame Packet.
		*/
		virtual Packet DemuxFrame() = 0;

	};

}