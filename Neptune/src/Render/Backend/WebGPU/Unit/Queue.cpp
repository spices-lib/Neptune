/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Queue.h"

namespace Neptune::WebGPU::Unit {

	Queue::~Queue()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuQueueRelease(m_Handle);
	}

	void Queue::CreateQueue(WGPUDevice device)
	{
		NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceGetQueue(device);
	}
	
	void Queue::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
    	
		wgpuQueueSetLabel(m_Handle, { name.c_str(), name.size() });
	}
	
}

#endif