/**
* @file PhysicalDevice.cpp.
* @brief The PhysicalDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "PhysicalDevice.h"
#include "Instance.h"
#include "KHR/Surface.h"

namespace Neptune::Vulkan {

	PhysicalDevice::PhysicalDevice(Context& context)
        : Infrastructure(context)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

    void PhysicalDevice::Create()
    {
		NEPTUNE_PROFILE_ZONE

        const auto instance = m_Context.Get<Instance>()->Handle();

		// Get all physical device num this computer.
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		// This software requires there must be at least one physical device.
        if (deviceCount == 0) 
		{
			NEPTUNE_CORE_ERROR("Failed to find GPUs with Vulkan support.")
			return;
		}

		// Get all physical device this computer.
        std::vector<VkPhysicalDevice> PhysicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, PhysicalDevices.data());

		// Iter all physical and select one suitable.
		for (const auto& physicalDevice : PhysicalDevices)
		{
			// All this condition need satisfied.
			if (IsExtensionMeetDemand(physicalDevice) && IsPropertyMeetDemand(physicalDevice) && IsFeatureMeetDemand(physicalDevice) &&
				IsQueueMeetDemand(physicalDevice, m_Context.Get<Surface>()->Handle()))
			{
				m_Handle = physicalDevice;

				NEPTUNE_CORE_INFO("Vulkan PhysicalDevice Selected.")
				return;
			}
		}

		NEPTUNE_CORE_ERROR("Failed to find GPU Physical Device that satisfied our needs.")
    }

	bool PhysicalDevice::IsExtensionMeetDemand(const VkPhysicalDevice& device)
	{
		NEPTUNE_PROFILE_ZONE

		// Get all physicaldevice extensions nums.
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		// Get all physicaldevice extensions that supported.
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		// Check whether all extensions satisfied.
		std::set<std::string> requiredExtensions;

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		if (requiredExtensions.empty())
		{
			return true;
		}
		else
		{
			// Get Physical Device name.
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);

			for (auto& set : requiredExtensions)
			{
				std::stringstream ss;
				ss << "Device Extension Required: [ " << set << " ], Which is not satisfied with device: " << deviceProperties.deviceName;

				NEPTUNE_CORE_ERROR(ss.str())
			}

			return false;
		}
	}

	bool PhysicalDevice::IsPropertyMeetDemand(const VkPhysicalDevice& device)
	{
		NEPTUNE_PROFILE_ZONE

		VkPhysicalDeviceProperties2                   prop2 {};
		prop2.sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		prop2.pNext                                 = nullptr;

		vkGetPhysicalDeviceProperties2(device, &prop2);

		return true;
	}

	bool PhysicalDevice::IsFeatureMeetDemand(const VkPhysicalDevice& device)
	{
		NEPTUNE_PROFILE_ZONE

		VkPhysicalDeviceFeatures2                             deviceFeatures {};
		deviceFeatures.sType                                = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		deviceFeatures.pNext                                = nullptr;

		vkGetPhysicalDeviceFeatures2(device, &deviceFeatures);

		return true;
	}

	bool PhysicalDevice::IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		NEPTUNE_PROFILE_ZONE

		// Get all physicaldevice queue nums.
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		// Get all physicaldevice queue that supported.
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		// Check queue identify.
		for (uint32_t i = 0; i < queueFamilyCount; i++) 
		{
			const auto& queueFamily = queueFamilies[i];

			/**
			* @brief Get graphic queue identify.
			*/
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

				// Get present queue identify.
				if (presentSupport) 
				{
				}
			}
			else
			{
				// Get compute queue identify.
				if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) 
				{
				}

				// Get transfer queue identify.
				if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) 
				{
				}
			}
		}

		return true;
	}

}

#endif