/**
* @file InfrastructureHeader.h.
* @brief The InfrastructureHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Render/Backend/WebGPU/Infrastructure/Instance.h"
#include "Render/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/WebGPU/Infrastructure/Surface.h"
#include "Render/Backend/WebGPU/Infrastructure/Adapter.h"
#include "Render/Backend/WebGPU/Infrastructure/Device.h"
#include "Render/Backend/WebGPU/Infrastructure/Queue.h"

#endif