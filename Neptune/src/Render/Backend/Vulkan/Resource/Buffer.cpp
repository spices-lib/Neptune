/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Buffer.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan {

	void Buffer::CreateBuffer(const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Has<IMemoryAllocator>() ? 
		m_Buffer.CreateBuffer(GetContext().Get<IMemoryAllocator>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties) : 
		m_Buffer.CreateBuffer(GetContext().Get<IPhysicalDevice>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties);
	}

	void Buffer::WriteToBuffer(const void* data, VkDeviceSize size, VkDeviceSize offset)
	{
		NEPTUNE_PROFILE_ZONE

		m_Buffer.WriteToBuffer(data, size, offset);
	}

	void Buffer::Flush(VkDeviceSize size, VkDeviceSize offset)
	{
		NEPTUNE_PROFILE_ZONE

		m_Buffer.Flush(size, offset);
	}

	void Buffer::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Buffer, name);
	}
}

#endif