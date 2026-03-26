/**
* @file Callback.cpp.
* @brief The Callback Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Callback.h"

namespace Neptune::WebGPU {

	void Callback::DeviceLostCallback(WGPUDevice const*, WGPUDeviceLostReason reason, WGPUStringView message, void*, void*)
	{
        NEPTUNE_PROFILE_ZONE

        const char* label = "";
        switch (reason)
        {
            case WGPUDeviceLostReason_Unknown:            label = "Unknown"; break;
            case WGPUDeviceLostReason_Destroyed:          label = "Destroyed"; break;
            case WGPUDeviceLostReason_CallbackCancelled:  label = "CallbackCancelled"; break;
            case WGPUDeviceLostReason_FailedCreation:     label = "FailedCreation"; break;
            default:                                      label = "Unknown";
        }

        std::stringstream ss;
        ss << "WebGPU DeviceLost: [ " << label << " ]: " << message.data;

        NEPTUNE_CORE_ERROR(ss.str())
	}

	void Callback::UncapturedErrorCallback(WGPUDevice const*, WGPUErrorType type, WGPUStringView message, void*, void*)
	{
        NEPTUNE_PROFILE_ZONE

		if (type == WGPUErrorType_NoError)
        {
            return;
        }

        const char* label = "";
        switch (type)
        {
            case WGPUErrorType_Validation:  label = "Validation"; break;
            case WGPUErrorType_OutOfMemory: label = "Out of memory"; break;
            case WGPUErrorType_Internal:    label = "Internal"; break;
            case WGPUErrorType_Unknown:     label = "Unknown"; break;
            default:                        label = "Unknown";
        }

        std::stringstream ss;
        ss << "WebGPU UncapturedError: [ " << label << " ]: " << message.data;

        NEPTUNE_CORE_ERROR(ss.str())
	}

}

#endif