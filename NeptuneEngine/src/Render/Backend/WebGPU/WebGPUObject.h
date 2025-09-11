/**
* @file WebGPUUtils.h.
* @brief The WebGPUObject Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "WebGPUContext.h"
#include "WebGPUUtils.h"

namespace Neptune {

    /**
    * @brief WebGPUObject Class.
    * This class defines the basic behaves of WebGPUObject.
    * When we create an new WebGPUObject, we need inherit from this.
    */
    class WebGPUObject : public NonCopyable, public std::enable_shared_from_this<WebGPUObject>
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPUContext.
        * @param[in] t EWebGPUObject.
        */
        WebGPUObject(WebGPUContext& context, EWebGPUObject t)
                : m_WebGPUContext(std::ref(context))
                , m_EWebGPUObject(t)
        {}

        /**
        * @brief Destructor Function.
        */
    	~WebGPUObject() override = default;

    protected:

        /**
        * @brief Registry this to WebGPUContext.
        */
        void Registry();

    protected:

        /**
        * @brief The global WebGPUContext Referenced from WebGPURenderBackend.
        */
        std::reference_wrapper<WebGPUContext> m_WebGPUContext;

        /**
        * @brief EWebGPUObject.
        */
        EWebGPUObject m_EWebGPUObject;
    };
}

#endif