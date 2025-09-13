/**
* @file VulkanInstance.cpp.
* @brief The VulkanInstance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanInstance.h"

namespace Neptune {

    VulkanInstance::VulkanInstance(VulkanContext& context)
        : VulkanInfrastructure(context)
    {
        Create();
    }

    void VulkanInstance::Create()
    {
        VkApplicationInfo                          appInfo {};
		appInfo.sType                            = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName                 = "neptune";
		appInfo.applicationVersion               = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName                      = "neptune";
		appInfo.engineVersion                    = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion                       = VK_API_VERSION_1_4;

        VkInstanceCreateInfo                       createInfo {};
		createInfo.sType                         = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo              = &appInfo;
		createInfo.pNext                         = nullptr;

        createInfo.enabledExtensionCount         = 0;
		createInfo.ppEnabledExtensionNames       = nullptr;

        createInfo.enabledLayerCount             = 0;
		createInfo.ppEnabledLayerNames           = nullptr;

        VK_CHECK(vkCreateInstance(&createInfo, nullptr, &m_Instance))
    }

}

#endif