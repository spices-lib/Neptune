#include "Pchheader.h"
#include "ContextAccessor.h"
#include "Context.h"
#include "Device.h"

namespace Neptune::Vulkan {

	VkDevice ContextAccessor::GetDevice() const
	{
		if (m_Context.Has<IDevice>())
		{
			return m_Context.Get<IDevice>()->Handle();
		}

		return nullptr;
	}
}