/**
* @file InfrastructureHeader.h.
* @brief The InfrastructureHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/Instance.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/Surface.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/Adapter.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/Queue.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/Future.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/CommandEncoder.h"

#endif