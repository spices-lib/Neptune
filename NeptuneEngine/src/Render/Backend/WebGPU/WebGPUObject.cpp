/**
* @file WebGPUObject.cpp.
* @brief The WebGPUObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUObject.h"

namespace Neptune {

	void WebGPUObject::Registry()
	{
		m_WebGPUContext.get().Registry(m_EWebGPUObject, shared_from_this());
	}

}

#endif