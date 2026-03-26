/**
* @file Infrastructure.cpp.
* @brief The Infrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Infrastructure.h"
#include "Instance.h"

namespace Neptune::WebGPU {
	
	InfrastructureBase::InfrastructureBase(Context& context)
		: m_Context(context)
	{}

	InfrastructureBase::~InfrastructureBase()
	{
		NEPTUNE_PROFILE_ZONE

		Release(this);
	}

	void InfrastructureBase::Wait(const WGPUFuture& future)
	{
		NEPTUNE_PROFILE_ZONE

		m_Context.Get<Instance>()->Wait(future);
	}

}

#endif