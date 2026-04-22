/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Version.h"
#include "Render/Backend/OpenGL/Infrastructure/ContextAccessor.h"
#include "Render/Frontend/Utils.h"

#include <functional>

namespace Neptune::Direct3D12 {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	constexpr D3D_FEATURE_LEVEL MinimumLevel { 
		D3D_FEATURE_LEVEL_11_0 
	};

	constexpr D3D_FEATURE_LEVEL FeatureLevels[5] {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_2,
	};

	#define DIRECT3D12_VERSION

	/**
	* @brief Result Delegate Class.
	*/
    struct HandleResultDelegate
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
	* @brief Handle Error Result.
	*
	* @param[in] result HRESULT.
	*/
	void HandleResult(HRESULT result);

	#define DIRECT3D12_CHECK(expr)  { auto expr_value = expr; if (FAILED(expr_value)) { std::invoke(HandleResultDelegate::GetHandler(), expr_value); } }
}

#endif