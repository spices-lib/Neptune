/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Device.h"
#include "PhysicalDevice.h"

namespace Neptune::Vulkan {

    Device::Device(Context& context)
        : Infrastructure(context)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Device::Create()
    {
		NEPTUNE_PROFILE_ZONE

        VkDeviceCreateInfo                                        createInfo{};
		createInfo.sType                                        = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos                            = nullptr;
		createInfo.queueCreateInfoCount                         = 0;
		createInfo.pEnabledFeatures                             = VK_NULL_HANDLE;
		createInfo.enabledExtensionCount                        = 0;
		createInfo.ppEnabledExtensionNames                      = nullptr;
		createInfo.enabledLayerCount                            = 0;
		createInfo.pNext                                        = nullptr;

		VK_CHECK(vkCreateDevice(m_Context.Get<PhysicalDevice>()->Handle(), &createInfo, nullptr, &m_Handle));
    }

}

#endif