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
	
		HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
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