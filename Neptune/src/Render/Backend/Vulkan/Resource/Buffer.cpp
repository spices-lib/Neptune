#include "Pchheader.h"
#include "Buffer.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Core/Math/Math.h"

namespace Neptune::Vulkan {

	void Buffer::CreateBuffer(const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		if (GetContext().Has<IMemoryAllocator>())
		{
			m_Buffer.CreateBuffer(
				GetContext().Get<IMemoryAllocator>()->Handle(),
				GetContext().Get<IDevice>()->Handle(),
				info,
				properties
			);
		}
		else
		{
			m_Buffer.CreateBuffer(
				GetContext().Get<IPhysicalDevice>()->Handle(),
				GetContext().Get<IDevice>()->Handle(),
				info,
				properties
			);
		}
	}

	void Buffer::WriteToBuffer(const void* data, VkDeviceSize size, VkDeviceSize offset)
	{
		m_Buffer.WriteToBuffer(data, size, offset);
	}

	void Buffer::Flush(VkDeviceSize size, VkDeviceSize offset)
	{
		m_Buffer.Flush(size, offset);
	}

	void Buffer::SetName(const std::string& name) const
	{
		DEBUGUTILS_SETOBJECTNAME(m_Buffer, name);
	}
}