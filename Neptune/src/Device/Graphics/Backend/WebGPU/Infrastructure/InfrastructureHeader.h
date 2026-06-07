/**
* @file InfrastructureHeader.h.
* @brief The InfrastructureHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Device/Graphics/Backend/WebGPU/Infrastructure/Instance.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Surface.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Adapter.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Queue.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Future.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/CommandEncoder.h"

#endif