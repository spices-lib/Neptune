/**
* @file Future.cpp.
* @brief The Future Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Future.h"
#include "Instance.h"

namespace Neptune::WebGPU {

    Future::Future(Context& context, EInfrastructure e, uint32_t count)
		: Infrastructure(context, e)
	{
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Future::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        m_Futures.resize(count);
    }
    
    void Future::SetHandle(uint32_t index, WGPUFuture handle)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto sp = CreateSP<Unit::Future>();
        
        sp->SetHandle(handle);
        
        m_Futures[index] = sp;
    }
    
    void Future::Wait(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (!m_Futures[index]) return;
        
        m_Futures[index]->Wait(GetContext().Get<IInstance>()->Handle());
    }

}

#endif