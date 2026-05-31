/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core.h"

namespace Neptune::WebGL {

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

}

#endif