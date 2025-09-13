/**
* @file WebGPUObject.cpp.
* @brief The WebGPUObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUObject.h"
#include "WebGPUInstance.h"

namespace Neptune {
	
	WebGPUObject::WebGPUObject(WebGPUContext& context)
		: m_Context(context)
	{
		m_Context.Registry(shared_from_this());
	}

	WebGPUObject::~WebGPUObject()
	{
		Release(this);
		
		m_Context.UnRegistry(shared_from_this());
	}

	void WebGPUObject::Wait(const WGPUFuture& future)
	{
		m_Context.Get<WebGPUInstance>()->Wait(future);
	}

}

#endif