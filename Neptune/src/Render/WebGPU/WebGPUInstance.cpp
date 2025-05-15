/**
* @file WebGPUInstance.cpp.
* @brief The WebGPUInstance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPUInstance.h"

namespace Neptune {

    WebGPUInstance::WebGPUInstance(
            WebGPUState&       webGPUState ,
            const std::string& name        ,
            const std::string& engineName
    )
            : WebGPUObject(webGPUState)
    {
        webGPUState.m_Instance = wgpuCreateInstance(nullptr);
    }





}