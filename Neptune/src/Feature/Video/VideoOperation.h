/**
* @file VideoOperation.h.
* @brief The VideoOperation Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

	/**
	* @brief Enum of Video Decode/Encode Operation.
	*/
	enum class VideoOperation : uint8_t
	{
		DecodeVP9 = 0,
		DecodeH264,
		DecodeH265,
		DecodeAV1,

		EncodeH264,
		EncodeH265,
		EncodeAV1,

		Count
	};

}