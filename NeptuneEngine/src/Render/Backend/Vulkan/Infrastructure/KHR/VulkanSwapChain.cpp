/**
* @file VulkanSwapChain.cpp.
* @brief The VulkanSwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanSwapChain.h"

namespace Neptune {

    VulkanSwapChain::VulkanSwapChain(VulkanContext& context)
        : VulkanInfrastructure(context)
    {
        Create();
    }

    void VulkanSwapChain::Create()
    {

    }

}

#endif