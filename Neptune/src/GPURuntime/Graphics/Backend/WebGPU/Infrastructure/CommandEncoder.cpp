/**
* @file CommandEncoder.cpp.
* @brief The CommandEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "CommandEncoder.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include "Render/Backend/WebGPU/Unit/CommandBuffer.h"

namespace Neptune::WebGPU {

    CommandEncoder::CommandEncoder(Context& context, EInfrastructure e, uint32_t count)
		: Infrastructure(context, e)
	{
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void CommandEncoder::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandEncoders.resize(count);
    }
    
    void CommandEncoder::Begin(uint32_t index)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto sp = CreateSP<Unit::CommandEncoder>();
        
        WGPUCommandEncoderDescriptor desc{};
        
        sp->CreateCommandEncoder(GetContext().Get<IDevice>()->Handle(), desc);
        
        m_CommandEncoders[index] = sp;
        
        DEBUGUTILS_SETOBJECTNAME(*sp, ToString())
    }
    
    SP<Unit::CommandBuffer> CommandEncoder::End(uint32_t index)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto sp = CreateSP<Unit::CommandBuffer>();
        
        WGPUCommandBufferDescriptor    desc{};
        sp->SetHandle(wgpuCommandEncoderFinish(m_CommandEncoders[index]->GetHandle(), &desc));
        
        DEBUGUTILS_SETOBJECTNAME(*sp, "CommandBuffer")
        
        m_CommandEncoders[index].reset();
        
        return sp;
    }

}

#endif