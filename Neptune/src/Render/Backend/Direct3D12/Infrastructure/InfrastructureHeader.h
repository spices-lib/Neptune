/**
* @file InfrastructureHeader.h.
* @brief The InfrastructureHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Render/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Direct3D12/Infrastructure/Factory.h"
#include "Render/Backend/Direct3D12/Infrastructure/Device.h"
#include "Render/Backend/Direct3D12/Infrastructure/Queue.h"
#include "Render/Backend/Direct3D12/Infrastructure/CommandAllocator.h"
#include "Render/Backend/Direct3D12/Infrastructure/CommandList.h"
#include "Render/Backend/Direct3D12/Infrastructure/Fence.h"
#include "Render/Backend/Direct3D12/Infrastructure/SwapChain.h"

#endif