/**
* @file VulkanDevice.cpp.
* @brief The VulkanDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanDevice.h"
#include "VulkanPhysicalDevice.h"

namespace Neptune {

    VulkanDevice::VulkanDevice(VulkanContext& context)
        : VulkanInfrastructure(context)
    {
        Create();
    }

    void VulkanDevice::Create()
    {
        VkDeviceCreateInfo                                        createInfo{};
		createInfo.sType                                        = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos                            = nullptr;
		createInfo.queueCreateInfoCount                         = 0;
		createInfo.pEnabledFeatures                             = VK_NULL_HANDLE;
		createInfo.enabledExtensionCount                        = 0;
		createInfo.ppEnabledExtensionNames                      = nullptr;
		createInfo.enabledLayerCount                            = 0;
		createInfo.pNext                                        = nullptr;

		VK_CHECK(vkCreateDevice(m_Context.Get<VulkanPhysicalDevice>()->Row(), &createInfo, nullptr, &m_Device));
    }

}

#endif