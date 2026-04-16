#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Render/Backend/Vulkan/Infrastructure/Instance.h"
#include "Render/Backend/Vulkan/Infrastructure/Functions.h"
#include "Render/Backend/Vulkan/Infrastructure/Surface.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/ThreadQueue.h"
#include "Render/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Render/Backend/Vulkan/Infrastructure/Semaphore.h"
#include "Render/Backend/Vulkan/Infrastructure/Fence.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/CommandPool.h"
#include "Render/Backend/Vulkan/Infrastructure/CommandBuffer.h"
#include "Render/Backend/Vulkan/Infrastructure/DescriptorPool.h"
#include "Render/Backend/Vulkan/Infrastructure/ThreadCommandPool.h"
#include "Render/Backend/Vulkan/Infrastructure/Queue.h"

#endif