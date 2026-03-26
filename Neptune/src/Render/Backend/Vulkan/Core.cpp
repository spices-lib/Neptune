#include "Pchheader.h"
#include "Core.h"
#include "Converter.h"

namespace Neptune::Vulkan {

	namespace {
	
		HandleVulkanResultDelegate::Handler s_Handler;
	}

	void HandleVulkanResultDelegate::SetHandler(const Handler& fn)
	{
		s_Handler = fn;
	}

	const HandleVulkanResultDelegate::Handler& HandleVulkanResultDelegate::GetHandler()
	{
		return s_Handler;
	}

	void HandleVulkanResult(VkResult result, VkPhysicalDevice physicalDevice, VkDevice device, PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT)
	{
		if (result == VK_SUCCESS) return;

		const char* label = "";
		switch (result)
		{
			case VK_NOT_READY:                                           label = "Not Ready";                           break;
			case VK_TIMEOUT:                                             label = "Time out";                            break;
			case VK_EVENT_SET:                                           label = "Event Set";                           break;
			case VK_EVENT_RESET:                                         label = "Event Reset";                         break;
			case VK_INCOMPLETE:                                          label = "Incomplete";                          break;
			case VK_ERROR_OUT_OF_HOST_MEMORY:                            label = "Out of Host Memory";                  break;
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:                          label = "Out of Device Memory";                break;
			case VK_ERROR_INITIALIZATION_FAILED:                         label = "Initialization Failed";               break;
			case VK_ERROR_DEVICE_LOST:                                   label = "Device Lost";                         break;
			case VK_ERROR_MEMORY_MAP_FAILED:                             label = "Memory Map Failed";                   break;
			case VK_ERROR_LAYER_NOT_PRESENT:                             label = "Layer not Present";                   break;
			case VK_ERROR_EXTENSION_NOT_PRESENT:                         label = "Extension not Present";               break;
			case VK_ERROR_FEATURE_NOT_PRESENT:                           label = "Feature not Present";                 break;
			case VK_ERROR_INCOMPATIBLE_DRIVER:                           label = "Incompatible Driver";                 break;
			case VK_ERROR_TOO_MANY_OBJECTS:                              label = "Too Many Objects";                    break;
			case VK_ERROR_FORMAT_NOT_SUPPORTED:                          label = "Format not supported";                break;
			case VK_ERROR_SURFACE_LOST_KHR:                              label = "Surface Lost";                        break;
			case VK_SUBOPTIMAL_KHR:                                      label = "Suboptimal";                          break;
			case VK_ERROR_OUT_OF_DATE_KHR:                               label = "Out of Data";                         break;
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                      label = "Incompatible Display";                break;
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                      label = "Native Window In Use";                break;
			case VK_ERROR_VALIDATION_FAILED_EXT:                         label = "Validation Failed";                   break;
			case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:        label = "Video Profile Format Not Supported";  break;
			default:                                                     label = "Unkonwn Error";                       break;
		}

		std::stringstream ss;
		ss << "Vulkan Error: [ " << label << " ]: ";

		if (result == VK_ERROR_DEVICE_LOST && vkGetDeviceFaultInfoEXT && device)
		{
            VkDeviceFaultCountsEXT                      faultCounts{};
            faultCounts.sType                         = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;

            VkResult result = vkGetDeviceFaultInfoEXT(device, &faultCounts, nullptr);
            if (result != VK_SUCCESS) 
            {
                CORE_ERROR("Device Lost: Failed to query fault counts.")
                return;
            }

            std::vector<VkDeviceFaultAddressInfoEXT> addressInfos(faultCounts.addressInfoCount);
            std::vector<VkDeviceFaultVendorInfoEXT> vendorInfos(faultCounts.vendorInfoCount);
            std::vector<uint8_t> vendorBinary(faultCounts.vendorBinarySize);

            VkDeviceFaultInfoEXT                        faultInfo{};
            faultInfo.sType                           = VK_STRUCTURE_TYPE_DEVICE_FAULT_INFO_EXT;
            faultInfo.pAddressInfos                   = addressInfos.data();
            faultInfo.pVendorInfos                    = vendorInfos.data();
            faultInfo.pVendorBinaryData               = vendorBinary.data();

            result = vkGetDeviceFaultInfoEXT(device, &faultCounts, &faultInfo);
            if (result != VK_SUCCESS && result != VK_INCOMPLETE) 
            {
                CORE_ERROR("Device Lost: Failed to query fault info.")
                return;
            }

            ss << "Description: " << faultInfo.description << "\n";

            for (uint32_t i = 0; i < faultCounts.addressInfoCount; i++) 
            {
                const auto& addr = addressInfos[i];
                const char* typeStr = "Unknown";
                switch (addr.addressType) 
                {
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_READ_INVALID_EXT: typeStr = "Invalid Read"; break;
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT: typeStr = "Invalid Write"; break;
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_EXECUTE_INVALID_EXT: typeStr = "Invalid Execute"; break;
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_FAULT_EXT: typeStr = "Instruction Pointer Fault"; break;
                }

                uint64_t lower = addr.reportedAddress & ~(addr.addressPrecision - 1);
                uint64_t upper = addr.reportedAddress | (addr.addressPrecision - 1);

                ss << "Address[" << i << "]: type = " << typeStr << ", reported = " << (unsigned long long)addr.reportedAddress << ", precision = " << (unsigned long long)addr.addressPrecision
                    << "Address range :" << (unsigned long long)lower << " - " << (unsigned long long)upper << "\n";
            }

            for (uint32_t i = 0; i < faultCounts.vendorInfoCount; i++) 
            {
                const auto& vendor = vendorInfos[i];
                
                ss << "Vendor[" << i << "]: description = " << vendor.description << "\n";
            }

            if (faultCounts.vendorBinarySize > 0) 
            {
                FILE* fp = fopen("DeviceLostDump.bin", "wb");
                fwrite(vendorBinary.data(), 1, faultCounts.vendorBinarySize, fp);
                fclose(fp);

                CORE_INFO("Device Lost Vendor binary crash dump saved to DeviceLostDump.bin")
            }

            CORE_ERROR(ss.str())
            return;
		}

        if ((result == VK_ERROR_OUT_OF_HOST_MEMORY || result == VK_ERROR_OUT_OF_DEVICE_MEMORY) && physicalDevice)
        {
            VkPhysicalDeviceMemoryBudgetPropertiesEXT      memoryBudgetProperties{};
            memoryBudgetProperties.sType                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
            memoryBudgetProperties.pNext                 = nullptr;

            VkPhysicalDeviceMemoryProperties2              memoryProperties{};
            memoryProperties.sType                       = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
            memoryProperties.pNext                       = &memoryBudgetProperties;

            vkGetPhysicalDeviceMemoryProperties2(physicalDevice, &memoryProperties);

            ss << "\n";

            for (uint64_t i = 0; i < memoryProperties.memoryProperties.memoryHeapCount; i++)
            {
                ss << "                        Heap: [ " << ToString(memoryProperties.memoryProperties.memoryHeaps[i].flags) << " ] Budget: [ " << memoryBudgetProperties.heapBudget[i] << " ] Usage: [ " << memoryBudgetProperties.heapUsage[i] << " ]\n";
            }

            CORE_ERROR(ss.str())
            return;
        }

		CORE_ERROR(ss.str())
	}
}