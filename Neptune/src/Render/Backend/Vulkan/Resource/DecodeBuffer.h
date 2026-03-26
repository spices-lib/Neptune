#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Buffer.h"
#include <vector>

namespace Neptune::Vulkan {

	class DecodeBuffer : public ContextAccessor
	{
	public:

		DecodeBuffer(Context& context) : ContextAccessor(context), m_Buffer(context) {}
		~DecodeBuffer() override = default;

		const VkDeviceSize& Size() const { return m_Buffer.Size(); }

		const Unit::Buffer::Handle& GetHandle() const { return m_Buffer.Handle(); }

		void CreateBuffer(VkDeviceSize size = 0);

		void WriteToBuffer(const void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		VkDeviceSize SetSliceStartCodeAtOffset(VkDeviceSize indx);

		bool HasSliceStartCodeAtOffset(VkDeviceSize indx) const;

		uint8_t* HostData();

		uint8_t Read(VkDeviceSize indx) const;

		uint32_t AddStreamMarker(uint32_t streamOffset);

		uint32_t ResetStreamMarkers();

		uint32_t GetStreamMarkersCount() const { return m_StreamMarkers.size(); }

		const uint32_t* GetStreamMarkersPtr(uint32_t startIndex, uint32_t& maxCount) const;

	private:

		Buffer                   m_Buffer;
		std::vector<uint32_t>    m_StreamMarkers;
	};
}