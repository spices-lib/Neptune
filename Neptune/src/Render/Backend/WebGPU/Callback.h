/**
* @file Callback.h.
* @brief The Callback Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Utils.h"

namespace Neptune::WebGPU {

    /**
    * @brief Callback Class.
    */
    class Callback
    {
    public:

        /**
        * @brief WebGPU Device Lost Callback.
        *
        * @param[in] type WGPUDeviceLostReason.
        * @param[in] message WGPUStringView.
        */
        static void DeviceLostCallback(WGPUDevice const*, WGPUDeviceLostReason reason, WGPUStringView message, void*, void*);

        /**
        * @brief WebGPU Uncaptured Error Callback.
        *
        * @param[in] type WGPUErrorType.
        * @param[in] message WGPUStringView.
        */
        static void UncapturedErrorCallback(WGPUDevice const*, WGPUErrorType type, WGPUStringView message, void*, void*);
        
    };

}

#endif