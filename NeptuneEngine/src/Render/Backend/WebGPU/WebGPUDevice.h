/**
* @file WebGPUDevice.h.
* @brief The WebGPUDevice Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUObject.h"

namespace Neptune {

    /**
    * @brief WebGPUDevice Class.
    */
    class WebGPUDevice : public WebGPUObject
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] context The global WebGPUContext.
        */
        WebGPUDevice(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUDevice() override = default;


    private:


    private:

        /**
        * @brief WGPUDevice.
        */
        WGPUDevice m_Device = nullptr;

    };
}

#endif