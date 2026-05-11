/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core.h"
#include "Converter.h"

namespace Neptune::Vulkan {

	namespace {
	
        HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT         messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT                messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT*    pCallbackData, 
		void*                                          pUserData
	) {
		NEPTUNE_PROFILE_ZONE

		std::stringstream ss;

		ss <<
		"Vulkan Validation layer:\n			" <<
		"MessageIdNumber: " <<
		pCallbackData->messageIdNumber <<
		"\n			MessageIdName: " <<
		pCallbackData->pMessageIdName;

		if (pCallbackData->cmdBufLabelCount != 0)
		{
			ss << "\n		CmdLabelName: " <<
			pCallbackData->pCmdBufLabels->pLabelName;
		}

		ss <<
		"\n			Message: " <<
		pCallbackData->pMessage;

		switch (messageSeverity)
		{
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			{
				NEPTUNE_CORE_TRACE(ss.str())
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			{
				NEPTUNE_CORE_INFO(ss.str())
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			{
				NEPTUNE_CORE_WARN(ss.str())
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			{
				NEPTUNE_CORE_ERROR(ss.str())
				break;
			}
			default:
			{
				NEPTUNE_CORE_INFO(ss.str())
				break;
			}
		}

		return VK_FALSE;
	}
	
	void HandleResult(VkResult result, VkPhysicalDevice physicalDevice, VkDevice device, PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == VK_SUCCESS) return;

		const char* label = "";
		switch (result)
		{
			case VK_NOT_READY:                                           label = "Not Ready";                                  break;
			case VK_TIMEOUT:                                             label = "Time out";                                   break;
			case VK_EVENT_SET:                                           label = "Event Set";                                  break;
			case VK_EVENT_RESET:                                         label = "Event Reset";                                break;
			case VK_INCOMPLETE:                                          label = "Incomplete";                                 break;
			case VK_ERROR_OUT_OF_HOST_MEMORY:                            label = "Out of Host Memory";                         break;
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:                          label = "Out of Device Memory";                       break;
			case VK_ERROR_INITIALIZATION_FAILED:                         label = "Initialization Failed";                      break;
			case VK_ERROR_DEVICE_LOST:                                   label = "Device Lost";                                break;
			case VK_ERROR_MEMORY_MAP_FAILED:                             label = "Memory Map Failed";                          break;
			case VK_ERROR_LAYER_NOT_PRESENT:                             label = "Layer not Present";                          break;
			case VK_ERROR_EXTENSION_NOT_PRESENT:                         label = "Extension not Present";                      break;
			case VK_ERROR_FEATURE_NOT_PRESENT:                           label = "Feature not Present";                        break;
			case VK_ERROR_INCOMPATIBLE_DRIVER:                           label = "Incompatible Driver";                        break;
			case VK_ERROR_TOO_MANY_OBJECTS:                              label = "Too Many Objects";                           break;
			case VK_ERROR_FORMAT_NOT_SUPPORTED:                          label = "Format not supported";                       break;
			case VK_ERROR_SURFACE_LOST_KHR:                              label = "Surface Lost";                               break;
			case VK_SUBOPTIMAL_KHR:                                      label = "Suboptimal";                                 break;
			case VK_ERROR_OUT_OF_DATE_KHR:                               label = "Out of Data";                                break;
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                      label = "Incompatible Display";                       break;
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                      label = "Native Window In Use";                       break;
			case VK_ERROR_VALIDATION_FAILED_EXT:                         label = "Validation Failed";                          break;
			case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:        label = "Video Profile Format Not Supported";         break;
			case VK_ERROR_FRAGMENTED_POOL:                               label = "Fragment Pool";                              break;
			case VK_ERROR_OUT_OF_POOL_MEMORY:                            label = "Out of Pool Memory";                         break;
			case VK_ERROR_INVALID_EXTERNAL_HANDLE:                       label = "Invalid External Handle";                    break;
			case VK_ERROR_FRAGMENTATION:                                 label = "Fragmentation";                              break;
			case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:                label = "Invalid Opaque Capture address";             break;
			case VK_ERROR_NOT_PERMITTED:                                 label = "Not Permitted";                              break;
			case VK_ERROR_INVALID_SHADER_NV:                             label = "Invalid Shader NV";                          break;
			case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:                 label = "Image Usage not supported";                  break;
			case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:        label = "Video Picture Layout not supported";         break;
			case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:     label = "Video Profile Operation Not Supported";      break;
			case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:         label = "Video Profile Codec Not Supported";          break;
			case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:           label = "Video STD Version Not Supported";            break;
			case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:  label = "Invalid DRM format modifier plane layout";   break;
			case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:           label = "Full screen exclusive mode lost";            break;
			case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:              label = "Invalid Video STD Parameters";               break;
			case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:                     label = "Compression Exhausted";                      break;
			case VK_INCOMPATIBLE_SHADER_BINARY_EXT:                      label = "Incompatible Shader Binary";                 break;
			case VK_PIPELINE_BINARY_MISSING_KHR:                         label = "Pipeline Binary Missing";                    break;
			case VK_ERROR_NOT_ENOUGH_SPACE_KHR:                          label = "Not enough space";                           break;
			case VK_PIPELINE_COMPILE_REQUIRED:                           label = "Pipeline Compile Required";                  break;
			case VK_THREAD_IDLE_KHR:                                     label = "Thread idle";                                break;
			case VK_THREAD_DONE_KHR:                                     label = "Thread none";                                break;
			case VK_OPERATION_DEFERRED_KHR:                              label = "Operation Deferred";                         break;
			case VK_OPERATION_NOT_DEFERRED_KHR:                          label = "Operation not deferred";                     break;
			case VK_ERROR_UNKNOWN:                                       label = "Unknown Error";                              break;
			default:                                                     label = "Unknown Error";                              break;
		}

		std::stringstream ss;
		ss << "Vulkan Error: [ " << label << " ]";

		if (result == VK_ERROR_DEVICE_LOST && vkGetDeviceFaultInfoEXT && device)
		{
            VkDeviceFaultCountsEXT                      faultCounts{};
            faultCounts.sType                         = VK_STRUCTURE_TYPE_DEVICE_FAULT_COUNTS_EXT;

            result = vkGetDeviceFaultInfoEXT(device, &faultCounts, nullptr);
            if (result != VK_SUCCESS) 
            {
                NEPTUNE_CORE_ERROR("Device Lost: Failed to Query Fault Counts.")
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
                NEPTUNE_CORE_ERROR("Device Lost: Failed to Query Fault Info.")
                return;
            }

            ss << "\n" << "Description: " << faultInfo.description << "\n";

            for (uint32_t i = 0; i < faultCounts.addressInfoCount; i++) 
            {
                const auto& addr = addressInfos[i];
                const char* typeStr = "Unknown";
                switch (addr.addressType) 
                {
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_READ_INVALID_EXT:                     typeStr = "Invalid Read";                break;
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_WRITE_INVALID_EXT:                    typeStr = "Invalid Write";               break;
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_EXECUTE_INVALID_EXT:                  typeStr = "Invalid Execute";             break;
                    case VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_FAULT_EXT:        typeStr = "Instruction Pointer Fault";   break;
					case VK_DEVICE_FAULT_ADDRESS_TYPE_NONE_EXT:                             typeStr = "Invalid Read";                break;
					case VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_UNKNOWN_EXT:      typeStr = "Instruction Pointer unknown"; break;
					case VK_DEVICE_FAULT_ADDRESS_TYPE_INSTRUCTION_POINTER_INVALID_EXT:      typeStr = "Instruction Pointer invalid"; break;
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
                FILE* fp = nullptr;
            	auto err = fopen_s(&fp, "DeviceLostDump.bin", "wb");
            	if (err == 0 && fp != nullptr)
            	{
            		fwrite(vendorBinary.data(), 1, faultCounts.vendorBinarySize, fp);
            		fclose(fp);
            		NEPTUNE_CORE_ERROR("Device Lost Vendor binary crash dump saved to DeviceLostDump.bin")
				}
	            else
	            {
	            	NEPTUNE_CORE_ERROR("Failed to save device lost dump file")
	            }
            }

            NEPTUNE_CORE_ERROR(ss.str())
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

            NEPTUNE_CORE_ERROR(ss.str())
            return;
        }

        NEPTUNE_CORE_ERROR(ss.str())
	}
}

#endif