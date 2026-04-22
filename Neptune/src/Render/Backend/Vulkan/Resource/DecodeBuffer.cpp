/**
* @file DecodeBuffer.cpp.
* @brief The DecodeBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "DecodeBuffer.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"

namespace Neptune::Vulkan {

	namespace {

		constexpr uint64_t VideoDecodeBufferDefaultSize = 2 * 1024 * 1024;
	}

	void DecodeBuffer::CreateBuffer(VkDeviceSize size)
	{
		NEPTUNE_PROFILE_ZONE

		auto physicalDevice = GetContext().Get<IPhysicalDevice>();

		VkVideoDecodeH265ProfileInfoKHR             decodeH265Profile{};
		decodeH265Profile.sType                   = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
		decodeH265Profile.stdProfileIdc           = STD_VIDEO_H265_PROFILE_IDC_MAIN;
		decodeH265Profile.pNext                   = nullptr;

		VkVideoProfileInfoKHR                       profile;
		profile.sType                             = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		profile.videoCodecOperation               = VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR;   // Can be any here ?
		profile.chromaSubsampling                 = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
		profile.lumaBitDepth                      = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profile.chromaBitDepth                    = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profile.pNext                             = &decodeH265Profile;

		auto property = physicalDevice->QueryVideoSessionProperty(profile);

		auto alignment = property.capabilities.minBitstreamBufferSizeAlignment;

		auto bufferSize = (((size ? size : VideoDecodeBufferDefaultSize) + (alignment - 1)) & ~(alignment - 1));

		VkBufferCreateInfo                   info{};
		info.sType                         = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		info.size                          = bufferSize;
		info.usage                         = VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR;
		info.flags                         = VK_BUFFER_CREATE_VIDEO_PROFILE_INDEPENDENT_BIT_KHR;
		info.sharingMode                   = VK_SHARING_MODE_EXCLUSIVE;
		info.queueFamilyIndexCount         = 1;
		info.pQueueFamilyIndices           = &physicalDevice->GetQueueFamilies().videoDecode.value();

		m_Buffer.CreateBuffer(info, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
	}

	void DecodeBuffer::WriteToBuffer(const void* data, VkDeviceSize size, VkDeviceSize offset)
	{
		NEPTUNE_PROFILE_ZONE

		/*VkVideoDecodeH265ProfileInfoKHR           decodeH265Profile{};
		decodeH265Profile.sType                   = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
		decodeH265Profile.stdProfileIdc           = STD_VIDEO_H265_PROFILE_IDC_MAIN;
		decodeH265Profile.pNext                   = nullptr;
										         
		VkVideoProfileInfoKHR                       profile{};
		profile.sType                             = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		profile.videoCodecOperation               = VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR;
		profile.chromaSubsampling                 = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
		profile.lumaBitDepth                      = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profile.chromaBitDepth                    = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profile.pNext                             = &decodeH265Profile;

		auto physicalDevice = GetContext().Get<IPhysicalDevice>();

		auto property = physicalDevice->QueryVideoSessionProperty({ profile });

		auto alignment = property.capabilities.minBitstreamBufferOffsetAlignment;

		offset = ((offset + (alignment - 1)) & ~(alignment - 1));*/

		m_Buffer.WriteToBuffer(data, size, offset);
	}

	VkDeviceSize DecodeBuffer::SetSliceStartCodeAtOffset(VkDeviceSize index) const
	{
		NEPTUNE_PROFILE_ZONE

		uint8_t* data = static_cast<uint8_t*>(m_Buffer.Data());

		assert(data && index < m_Buffer.Size());

		data[index + 0] = 0x00;
		data[index + 1] = 0x00;
		data[index + 2] = 0x01;

		return 3;
	}

	bool DecodeBuffer::HasSliceStartCodeAtOffset(VkDeviceSize indx) const
	{
		NEPTUNE_PROFILE_ZONE

		assert(indx < m_Buffer.Size());

		const uint8_t* data = static_cast<uint8_t*>(m_Buffer.Data());

		return ((data[indx + 0] == 0x00) && (data[indx + 1] == 0x00) && (data[indx + 2] == 0x01));
	}

	uint8_t* DecodeBuffer::HostData() const
	{
		NEPTUNE_PROFILE_ZONE

		return static_cast<uint8_t*>(m_Buffer.Data());
	}

	uint8_t DecodeBuffer::Read(VkDeviceSize index) const
	{
		NEPTUNE_PROFILE_ZONE

		const uint8_t* data = static_cast<uint8_t*>(m_Buffer.Data());

		assert(data && index < m_Buffer.Size());

		return data[index];
	}

	uint32_t DecodeBuffer::AddStreamMarker(uint32_t streamOffset)
	{
		NEPTUNE_PROFILE_ZONE

		m_StreamMarkers.emplace_back(streamOffset);

		return (uint32_t)(m_StreamMarkers.size() - 1);
	}

	uint32_t DecodeBuffer::ResetStreamMarkers()
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t oldSize = (uint32_t)m_StreamMarkers.size();

		m_StreamMarkers.clear();

		return oldSize;
	}

	const uint32_t* DecodeBuffer::GetStreamMarkersPtr(uint32_t startIndex, uint32_t& maxCount) const
	{
		NEPTUNE_PROFILE_ZONE

		maxCount = (uint32_t)m_StreamMarkers.size() - startIndex;

		return m_StreamMarkers.data() + startIndex;
	}
}

#endif