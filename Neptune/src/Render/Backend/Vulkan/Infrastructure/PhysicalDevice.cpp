/**
* @file PhysicalDevice.cpp.
* @brief The PhysicalDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "PhysicalDevice.h"
#include "Device.h"
#include "Instance.h"
#include "Surface.h"
#include "Functions.h"

namespace Neptune::Vulkan {

	PhysicalDevice::PhysicalDevice(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	void PhysicalDevice::Create()
    {
		NEPTUNE_PROFILE_ZONE

        const auto instance = GetContext().Get<IInstance>()->Handle();

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) 
		{
			NEPTUNE_CORE_ERROR("Failed to find GPUs with Vulkan support.")
			return;
		}

        std::vector<VkPhysicalDevice> PhysicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, PhysicalDevices.data());

		// Iter all physical and select one suitable.
		for (const auto& physicalDevice : PhysicalDevices)
		{
			// All this condition need satisfied.
			if (IsExtensionMeetDemand(physicalDevice) && IsPropertyMeetDemand(physicalDevice) && IsFeatureMeetDemand(physicalDevice) &&
				IsQueueMeetDemand(physicalDevice, GetContext().Get<ISurface>()->Handle()))
			{
				m_PhysicalDevice.SetHandle(physicalDevice);

				NEPTUNE_CORE_INFO("Vulkan PhysicalDevice Selected.")
				return;
			}
		}

		NEPTUNE_CORE_ERROR("Failed to find GPU Physical Device that satisfied our needs.")
    }

	bool PhysicalDevice::IsExtensionMeetDemand(const VkPhysicalDevice& device) const
	{
		NEPTUNE_PROFILE_ZONE

		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		auto requiredList = GetExtensionRequirements();
		std::set<std::string> requiredExtensions(requiredList.begin(), requiredList.end());

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

		VkPhysicalDeviceOpticalFlowPropertiesNV       flowProps{};
		flowProps.sType                             = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_OPTICAL_FLOW_PROPERTIES_NV;
		flowProps.pNext                             = nullptr;

		VkPhysicalDeviceProperties2                   prop2 {};
		prop2.sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		prop2.pNext                                 = &flowProps;

		vkGetPhysicalDeviceProperties2(device, &prop2);

		m_Properties = prop2.properties;

		return true;
	}

	bool PhysicalDevice::IsFeatureMeetDemand(const VkPhysicalDevice& device) const
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

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties2> queueFamilies(queueFamilyCount,{ VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
		vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, queueFamilies.data());

		for (uint32_t i = 0; i < queueFamilyCount; i++) 
		{
			const auto& queueFamily = queueFamilies[i];

			if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				m_QueueFamilies.graphic = i;

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

				if (presentSupport) 
				{
					m_QueueFamilies.present = i;
				}
			}
			else
			{
				// Get compute queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT && !m_QueueFamilies.compute) 
				{
					m_QueueFamilies.compute = i;
				}

				// Get transfer queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT && !m_QueueFamilies.transfer) 
				{
					m_QueueFamilies.transfer = i;
				}

				// Get video encode queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR && !m_QueueFamilies.videoEncode)
				{
					m_QueueFamilies.videoEncode = i;
				}

				// Get video decode queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR && !m_QueueFamilies.videoDecode)
				{
					m_QueueFamilies.videoDecode = i;
				}

				// Get video decode queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV && !m_QueueFamilies.opticalFlow)
				{
					m_QueueFamilies.opticalFlow = i;
				}
			}

			if (m_QueueFamilies.isComplete()) return true;
		}

		return false;
	}

	bool PhysicalDevice::IsOpticalFlowSessionSupport(VkFormat format, VkOpticalFlowUsageFlagsNV usage)
	{
		NEPTUNE_PROFILE_ZONE

		VkOpticalFlowImageFormatInfoNV         formatInfo{};
		formatInfo.sType                     = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
		formatInfo.usage                     = usage;

		uint32_t count = 0;
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceOpticalFlowImageFormatsNV(Handle(), &formatInfo, &count, nullptr))

		std::vector<VkOpticalFlowImageFormatPropertiesNV> formats(count, { VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV });
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceOpticalFlowImageFormatsNV(Handle(), &formatInfo, &count, formats.data()))

		if (!std::ranges::any_of(formats.begin(), formats.end(), [&](const auto& f) { return f.format == format; }))
		{
			NEPTUNE_CORE_ERROR("Format Not Supported In OpticalFlowSession.")
			return false;
		}

		VkFormatProperties3                    properties3{};
		properties3.sType                    = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3;
		
		VkFormatProperties2                    properties2{}; 
		properties2.sType                    = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
		properties2.pNext                    = &properties3;

		vkGetPhysicalDeviceFormatProperties2(Handle(), format, &properties2);
		if (usage & VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV && !(properties3.optimalTilingFeatures & VK_FORMAT_FEATURE_2_OPTICAL_FLOW_IMAGE_BIT_NV))
		{
			NEPTUNE_CORE_ERROR("VK_FORMAT_FEATURE_2_OPTICAL_FLOW_IMAGE_BIT_NV Not Supported OPTICAL_FLOW_IMAGE_BIT.")
			return false;
		}

		if (usage & VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV && !(properties3.optimalTilingFeatures & VK_FORMAT_FEATURE_2_OPTICAL_FLOW_VECTOR_BIT_NV))
		{
			NEPTUNE_CORE_ERROR("VK_FORMAT_FEATURE_2_OPTICAL_FLOW_IMAGE_BIT_NV Not Supported OPTICAL_FLOW_VECTOR_BIT.")
			return false;
		}

		VkPhysicalDeviceImageFormatInfo2       formatInfo2{};
		formatInfo2.sType                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
		formatInfo2.format                   = format;
		formatInfo2.type                     = VK_IMAGE_TYPE_2D;
		formatInfo2.tiling                   = VK_IMAGE_TILING_OPTIMAL;
		formatInfo2.usage                    = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		formatInfo2.pNext                    = &formatInfo;

		VkImageFormatProperties2               formatProperties2{};
		formatProperties2.sType              = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;

		VK_CHECK(vkGetPhysicalDeviceImageFormatProperties2(Handle(), &formatInfo2, &formatProperties2))

		return true;
	}

	VideoSessionProperty PhysicalDevice::QueryVideoSessionProperty(const VkVideoProfileInfoKHR& videoProfile)
	{
		NEPTUNE_PROFILE_ZONE

		static VkVideoEncodeAV1CapabilitiesKHR       encodeAV1Capabilities { VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_CAPABILITIES_KHR };
		static VkVideoEncodeH264CapabilitiesKHR      encodeH264Capabilities{ VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_KHR };
		static VkVideoEncodeH265CapabilitiesKHR      encodeH265Capabilities{ VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_CAPABILITIES_KHR };
		static VkVideoEncodeCapabilitiesKHR          encodeCapabilities    { VK_STRUCTURE_TYPE_VIDEO_ENCODE_CAPABILITIES_KHR };

		static VkVideoDecodeVP9CapabilitiesKHR       decodeVP9Capabilities { VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_CAPABILITIES_KHR };
		static VkVideoDecodeAV1CapabilitiesKHR       decodeAV1Capabilities { VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_CAPABILITIES_KHR };
		static VkVideoDecodeH264CapabilitiesKHR      decodeH264Capabilities{ VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR };
		static VkVideoDecodeH265CapabilitiesKHR      decodeH265Capabilities{ VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR };
		static VkVideoDecodeCapabilitiesKHR          decodeCapabilities    { VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR };

		VideoSessionProperty                       property{};

		VkVideoCapabilitiesKHR&                    capabilities = property.capabilities;
		capabilities.sType                      = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;

		switch (videoProfile.videoCodecOperation)
		{
			case VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR:
			{
				decodeCapabilities.pNext        = &encodeH264Capabilities;
				capabilities.pNext              = &encodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR:
			{
				decodeCapabilities.pNext        = &encodeH265Capabilities;
				capabilities.pNext              = &encodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeH264Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeH265Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeAV1Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_BIT_KHR:
			{
				decodeCapabilities.pNext        = &encodeAV1Capabilities;
				capabilities.pNext              = &encodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeVP9Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
		}

		VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceVideoCapabilitiesKHR(Handle(), &videoProfile, &capabilities));

		if (decodeCapabilities.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR)
		{
			 // NV, Intel
			auto dpbFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR | VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR, { videoProfile });

            property.dpbFormat = dpbFormats[0];
            property.dstFormat = dpbFormats[0];
		}
		else if (decodeCapabilities.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_DISTINCT_BIT_KHR)
		{
			// AMD
			auto dpbFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR, { videoProfile });
            auto outFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR, { videoProfile });
           
            property.dpbFormat = dpbFormats[0];
            property.dstFormat = outFormats[0];
		}
		else
		{
			NEPTUNE_CORE_ERROR("Unsupported Decode Capability Flags.");
        }

		// Use One DPB as dst image.
		assert(property.dpbFormat == property.dstFormat);

		return property;
	}

	bool PhysicalDevice::IsOpticalFlowSessionSupport(VkFormat inputFormat, VkFormat outFormat)
	{
		NEPTUNE_PROFILE_ZONE

		bool result = true;

		result &= IsOpticalFlowSessionSupport(inputFormat, VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV);
		result &= IsOpticalFlowSessionSupport(outFormat, VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV);

		return result;
	}

	const SwapChainProperty& PhysicalDevice::QuerySwapChainProperty()
	{
		NEPTUNE_PROFILE_ZONE

		auto surface = GetContext().Get<ISurface>()->Handle();

		SwapChainProperty property{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Handle(), surface, &property.capabilities);

		if (property.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			property.surfaceSize = property.capabilities.currentExtent;
		}
		else
		{
			NEPTUNE_CORE_ERROR("Surface Extent is infinality.")
		}

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(Handle(), surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			property.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(Handle(), surface, &formatCount, property.formats.data());

			property.format = property.formats[0];

			for (const auto& availableFormat : property.formats)
			{
				if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM  &&
					availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					property.format = availableFormat;
					break;
				}
			}
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(Handle(), surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			property.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(Handle(), surface, &presentModeCount, property.presentModes.data());

			property.presentMode = property.presentModes[0];

			for (const auto& availablePresentMode : property.presentModes)
			{
				if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					property.presentMode = availablePresentMode;
					break;
				}
			}
		}

		m_SwapChainProperty = property;

		return m_SwapChainProperty;
	}

	const std::vector<const char*>& PhysicalDevice::GetExtensionRequirements() const
	{
		NEPTUNE_PROFILE_ZONE

		static std::vector<const char*> m_ExtensionProperties;

		if (m_ExtensionProperties.empty())
		{
			m_ExtensionProperties.push_back(VK_EXT_DEVICE_FAULT_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_MAINTENANCE_1_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SHADER_CLOCK_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SPIRV_1_4_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_EXT_MESH_SHADER_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);

			// @brief Video Decode/Encode
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_QUEUE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME);

			// @brief Optical Flow
			//m_ExtensionProperties.push_back(VK_NV_OPTICAL_FLOW_EXTENSION_NAME);
			 
			// @brief RayTracing
			m_ExtensionProperties.push_back(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_RAY_QUERY_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
		}

		return m_ExtensionProperties;
	}

	std::vector<VkFormat> PhysicalDevice::GetVideoFormats(VkImageUsageFlags imageUsage, const std::vector<VkVideoProfileInfoKHR>& videoProfile)
	{
		NEPTUNE_PROFILE_ZONE

		VkVideoProfileListInfoKHR                videoProfiles{};
		videoProfiles.sType                    = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
		videoProfiles.profileCount             = videoProfile.size();
		videoProfiles.pProfiles                = videoProfile.data();
		videoProfiles.pNext                    = nullptr;
		
		VkPhysicalDeviceVideoFormatInfoKHR       videoFormatInfo {};
		videoFormatInfo.sType                  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
		videoFormatInfo.imageUsage             = imageUsage;
		videoFormatInfo.pNext                  = &videoProfiles;

		uint32_t supportedFormatCount = 0;
        VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceVideoFormatPropertiesKHR(Handle(), &videoFormatInfo, &supportedFormatCount, nullptr))

		std::vector<VkVideoFormatPropertiesKHR> supportedFormats(supportedFormatCount, { VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR });
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceVideoFormatPropertiesKHR(Handle(), &videoFormatInfo, &supportedFormatCount, supportedFormats.data()))

		std::vector<VkFormat> formats;
		std::ranges::for_each(supportedFormats, [&](const auto& format){
			formats.emplace_back(format.format);
		});

		return formats;
	}
}

#endif