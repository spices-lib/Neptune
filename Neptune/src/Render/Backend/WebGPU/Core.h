/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/Utils.h"

#include <functional>
#include <webgpu.h>

namespace Neptune::WebGPU {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	constexpr uint64_t WaitTimeoutNS = 5E9;                                // @brief wgpuInstanceWaitAny timeoutNS.

	#define WEBGPUGL_VERSION                                               // @brief Use WEBGPU .

	/**
	* @brief Result Delegate Class.
	*/
    struct HandleResultDelegate
    {
        using Handler     = std::function<void(WGPUStatus)>;
		using WaitHandler = std::function<void(WGPUWaitStatus)>;

		/**
		* @brief Set Handler.
		* 
		* @param[in] fn Handler.
		*/
        static void SetHandler(const Handler& fn);

		/**
		* @brief Get Handler.
		*
		* @return Returns Handler.
		*/
        static const Handler& GetHandler();

		/**
		* @brief Set WaitHandler.
		*
		* @param[in] fn WaitHandler.
		*/
		static void SetWaitHandler(const WaitHandler& fn);

		/**
		* @brief Get WaitHandler.
		*
		* @return Returns WaitHandler.
		*/
		static const Handler& GetWaitHandler();
    };
	
	/**
	* @brief Handle Error Result.
	*
	* @param[in] result WGPUStatus.
	*/
	void HandleResult(WGPUStatus result);

	/**
	* @brief Handle Error Wait Result.
	*
	* @param[in] result WGPUWaitStatus.
	*/
	void HandleWaitResult(WGPUWaitStatus result);

	#define WEBGPU_CHECK(expr) { auto expr_value = expr; if (expr_value != WGPUStatus_Success) { std::invoke(HandleResultDelegate::GetHandler(), expr_value); } }
	#define WEBGPU_WAIT_CHECK(expr) { auto expr_value = expr; if (expr_value != WGPUWaitStatus_Success) { std::invoke(HandleResultDelegate::GetWaitHandler(), expr_value); } }
}

#endif