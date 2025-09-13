/**
* @file WebGPUCallback.h.
* @brief The WebGPUCallback Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUUtils.h"

namespace Neptune {

    /**
    * @brief WebGPUCallback Class.
    */
    class WebGPUCallback
    {
    public:

        /**
        * @brief WebGPU Device Lost Callback.
        *
        * @param[in] type WGPUDeviceLostReason.
        * @param[in] message WGPUStringView.
        */
        static void WebGPUDeviceLostCallback(WGPUDevice const*, WGPUDeviceLostReason reason, WGPUStringView message, void*, void*);

        /**
        * @brief WebGPU Uncaptured Error Callback.
        *
        * @param[in] type WGPUErrorType.
        * @param[in] message WGPUStringView.
        */
        static void WebGPUUncapturedErrorCallback(WGPUDevice const*, WGPUErrorType type, WGPUStringView message, void*, void*);
        
    };

}

#endif