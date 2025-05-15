/**
* @file WebGPUDevice.cpp.
* @brief The WebGPUDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WebGPUDevice.h"

#include <emscripten/html5_webgpu.h>

namespace Neptune {

    WebGPUDevice::WebGPUDevice(
            WebGPUState&       webGPUState ,
            const std::string& name        ,
            const std::string& engineName
    )
            : WebGPUObject(webGPUState)
    {

#ifdef __EMSCRIPTEN__

        webGPUState.m_Device = emscripten_webgpu_get_device();
        if (!webGPUState.m_Device)
            return;

#else

        WGPUAdapter adapter = RequestAdapter(webGPUState.m_Instance);
        if (!adapter)
            return false;
        webGPUState.m_Device = RequestDevice(adapter);

#endif

    }





}