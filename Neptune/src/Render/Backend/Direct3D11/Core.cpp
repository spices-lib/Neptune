/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Core.h"

namespace Neptune::Direct3D11 {

	namespace {
	
		HandleDirect3D11ResultDelegate::Handler s_Handler;   // @brief HandleDirect3D12ResultDelegate::Handler instance.
	}

	void HandleDirect3D11ResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleDirect3D11ResultDelegate::Handler& HandleDirect3D11ResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void HandleDirect3D11Result(HRESULT result)
	{
        NEPTUNE_PROFILE_ZONE

		if (!FAILED(result)) return;

		const char* label = "";
		switch (result)
		{
			default:                                                     label = "Unknown Error";                       break;
		}

		std::stringstream ss;
		ss << "Direct3D11 Error: [ " << label << " ]: ";

        NEPTUNE_CORE_ERROR(ss.str())
	}
}

#endif