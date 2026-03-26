#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"

namespace Neptune::Vulkan {

	class Buffer : public ContextAccessor
	{
	public:

		Buffer(Context& context) : ContextAccessor(context) {}
		~Buffer() override = default;

		const Unit::Buffer::Handle& Handle() const { return m_Buffer.GetHandle(); }

		const VkDeviceSize& Size() const { return m_Buffer.Size(); }

		void* Data() const { return m_Buffer.HostMemory(); }

		void CreateBuffer(const VkBufferCreateInfo& capabilities, VkMemoryPropertyFlags properties);

		void WriteToBuffer(const void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		void Flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		void SetName(const std::string& name) const;

	private:

		Unit::Buffer m_Buffer;
	};
}