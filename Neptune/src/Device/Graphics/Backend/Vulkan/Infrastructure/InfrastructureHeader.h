/**
* @file InfrastructureHeader.h.
* @brief The InfrastructureHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Device/Graphics/Backend/Vulkan/Infrastructure/Instance.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Functions.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Surface.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/ThreadQueue.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Semaphore.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Fence.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/CommandPool.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/CommandBuffer.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DescriptorPool.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/ThreadCommandPool.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Queue.h"

#endif