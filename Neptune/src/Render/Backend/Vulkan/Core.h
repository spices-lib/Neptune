#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/ContextAccessor.h"
#include "Render/Frontend/Utils.h"
#include <vulkan/vulkan.h>
#include <sstream>
#include <vector>
#include <functional>

namespace Neptune::Vulkan {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;

	constexpr uint32_t NThreadQueue = 4;

	constexpr uint32_t MaxDPBSlots = 16;

	#define VK_VERSION VK_API_VERSION_1_4

	#define VKImageHostOperation 0

    struct HandleVulkanResultDelegate
    {
        using Handler = std::function<void(VkResult)>;

        static void SetHandler(const Handler& fn);

        static const Handler& GetHandler();
    };

	void HandleVulkanResult(VkResult result, VkPhysicalDevice physicalDevice, VkDevice device, PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT);

	#define VK_CHECK(expr)  { auto expr_value = expr; if (expr_value != VK_SUCCESS) { std::invoke(HandleVulkanResultDelegate::GetHandler(), expr_value); } }
}