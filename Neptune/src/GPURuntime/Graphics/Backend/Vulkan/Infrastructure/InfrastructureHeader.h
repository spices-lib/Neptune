/**
* @file InfrastructureHeader.h.
* @brief The InfrastructureHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Instance.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Functions.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Surface.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/ThreadQueue.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Semaphore.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Fence.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/CommandPool.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/CommandBuffer.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/DescriptorPool.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/ThreadCommandPool.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Queue.h"

#endif