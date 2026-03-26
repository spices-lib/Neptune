#pragma once
#include <functional>

namespace Neptune::Vulkan {

	struct ClientDelegate
	{
		std::function<int32_t(const class VkParserSequenceInfo*)> BeginSequence;
		std::function<bool(class VkParserPictureData*)>           DecodePicture;
		std::function<bool(class VkPicIf**)>                      AllocPictureBuffer;
		std::function<bool(class VkPicIf*, int64_t)>              DisplayPicture;
	};

}