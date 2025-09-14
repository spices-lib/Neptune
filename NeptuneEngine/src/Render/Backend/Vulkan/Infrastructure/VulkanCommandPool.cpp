/**
* @file VulkanCommandPool.cpp.
* @brief The VulkanCommandPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanCommandPool.h"

namespace Neptune {

    VulkanCommandPool::VulkanCommandPool(VulkanContext& context)
        : VulkanInfrastructure(context)
    {
        Create();
    }

    void VulkanCommandPool::Create()
    {

    }

}

#endif