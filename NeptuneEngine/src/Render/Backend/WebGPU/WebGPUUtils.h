/**
* @file WebGPUUtils.h.
* @brief The WebGPUUtils Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"

#include <webgpu.h>

namespace Neptune {

    /**
    * @brief Max In Flight Frame.
    * 2 buffers are enough in this program.
    */
    constexpr uint32_t MaxFrameInFlight = 2;
 
    /**
    * @brief wgpuInstanceWaitAny timeoutNS.
    * default 5s.
    */
    constexpr uint64_t WaitTimeoutNS = 5E9;

    /**
    * @brief Handle WebGPUStatus Function.
    * @param[in] statue WebGPUStatus.
    */
    static void HandleWebGPUResult(WGPUStatus statue)
    {
        switch (statue)
        {
            case WGPUStatus_Success:
            {
                return;
            }
            case WGPUWaitStatus_Error:
            {
                NEPTUNE_CORE_ERROR("WebGPU Status Error.")
                    return;
            }
            default:
            {
                NEPTUNE_CORE_ERROR("WebGPU Status Unkonwn Error.")
            }
        }
    }

    /**
    * @brief Handle WGPUWaitStatus Function.
    * @param[in] statue WGPUWaitStatus.
    */
    static void HandleWebGPUWaitResult(WGPUWaitStatus statue)
    {
        switch (statue)
        {
            case WGPUStatus_Success: 
            {
                return;
            }
            case WGPUWaitStatus_TimedOut:
            {
                NEPTUNE_CORE_ERROR("WebGPU Wait Status TimedOut.")
                return;
            }
            case WGPUWaitStatus_Error:
            {
                NEPTUNE_CORE_ERROR("WebGPU Wait Status Error.")
                return;
            }
            default:
            {
                NEPTUNE_CORE_ERROR("WebGPU Wait Status Unkonwn Error.")
            }
        }
    }
 
    /**
    * @brief WebGPU Check macro.
    */
    #define WEBGPU_CHECK(expr)  { auto expr_value = expr; HandleWebGPUResult(expr_value); }

    /**
    * @brief WebGPU Wait Check macro.
    */
    #define WEBGPU_WAITCHECK(expr)  { auto expr_value = expr; HandleWebGPUWaitResult(expr_value); }

}

#endif