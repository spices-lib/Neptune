/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Version.h"
#include "Render/Backend/Direct3D11/Infrastructure/ContextAccessor.h"
#include "Render/Frontend/Utils.h"

#include <functional>

namespace Neptune::Direct3D11 {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	#define DIRECT3D11_VERSION

	/**
	* @brief Direct3D11Result Delegate Class.
	*/
    struct HandleDirect3D11ResultDelegate
    {
        using Handler = std::function<void(HRESULT)>;

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
    };
	
	/**
	* @brief Handle Direct3D11 Error Result.
	*
	* @param[in] result HRESULT.
	*/
	void HandleDirect3D11Result(HRESULT result);

	#define DIRECT3D11_CHECK(expr)  { auto expr_value = expr; if (FAILED(expr_value)) { std::invoke(HandleDirect3D11ResultDelegate::GetHandler(), expr_value); } }
}

#endif