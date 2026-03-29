/**
* @file CommandPool.cpp.
* @brief The CommandPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "CommandPool.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include "PhysicalDevice.h"

namespace Neptune::Vulkan {

    CommandPool::CommandPool(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void CommandPool::Create()
    {
        NEPTUNE_PROFILE_ZONE

        VkCommandPoolCreateInfo               poolInfo{};
		poolInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags                      = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex           = GetQueueFamily();

        m_CommandPool.CreateCommandPool(GetContext().Get<IDevice>()->Handle(), poolInfo);

        DEBUGUTILS_SETOBJECTNAME(m_CommandPool, ToString())
    }

    uint32_t CommandPool::GetQueueFamily() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (GetInfrastructure())
		{
			case EInfrastructure::GraphicCommandPool:	return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value();
			case EInfrastructure::ComputeCommandPool:   return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().compute.value();
			default: return 0;
		}
    }
}