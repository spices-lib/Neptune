/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core.h"

namespace Neptune::WebGPU {

	namespace {
	
		HandleResultDelegate::Handler     s_Handler;       // @brief HandleResultDelegate::Handler instance.
		HandleResultDelegate::WaitHandler s_WaitHandler;   // @brief HandleResultDelegate::WaitHandler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void HandleResultDelegate::SetWaitHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_WaitHandler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetWaitHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_WaitHandler;
	}
	
	void HandleResult(WGPUStatus result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == WGPUStatus_Success) return;

		const char* label = "";
		switch (result)
		{
			case WGPUStatus_Error:                                       label = "Error";                               break;
			default:                                                     label = "Unknown Error";                       break;
		}

		std::stringstream ss;
		ss << "WebGPU Error: [ " << label << " ]";

        NEPTUNE_CORE_ERROR(ss.str())
	}

	void HandleWaitResult(WGPUWaitStatus result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == WGPUWaitStatus_Success) return;

		const char* label = "";
		switch (result)
		{
			case WGPUWaitStatus_TimedOut:                                label = "Wait TimeOut";                        break;
			case WGPUWaitStatus_Error:                                   label = "Wait Error";                          break;
			default:                                                     label = "Unknown Error";                       break;
		}

		std::stringstream ss;
		ss << "WebGPU Error: [ " << label << " ]";

        NEPTUNE_CORE_ERROR(ss.str())
	}
}

#endif