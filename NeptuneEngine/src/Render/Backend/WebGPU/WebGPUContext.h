/**
* @file WebGPUContext.h.
* @brief The WebGPUContext Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

    class WebGPUObject;
    class WebGPUInstance;
    class WebGPUAdapter;
    class WebGPUDevice;

    enum class EWebGPUObject
    {
        WebGPUInstance,
        WebGPUAdapter,
        WebGPUDevice
    };

    /**
    * @brief This context contains all WebGPU object in used global.
    */
    class WebGPUContext : NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        WebGPUContext() = default;

        /**
        * @brief Destructor Function.
        */
        ~WebGPUContext() override = default;

        /**
        * @brief Registry WebGPUObject to this context.
        * 
        * @param[in] type EWebGPUObject.
        * @param[in] object WebGPUObject pointer.
        */
        void Registry(EWebGPUObject type, SP<WebGPUObject> object);

    private:

        SP<WebGPUInstance>  m_Instance;  // @brief WebGPUInstance
        SP<WebGPUAdapter>   m_Adapter;   // @brief WebGPUAdapter
        SP<WebGPUDevice>    m_Device;    // @brief WebGPUDevice
    };

}

#endif