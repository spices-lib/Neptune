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
    class WebGPUObject : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUObject(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
    	~WebGPUObject() override;

    public:

        /**
        * @brief Get EWebGPUObject.
        * 
        * @return Returns EWebGPUObject.
        */
        virtual const EWebGPUObject& GetType() const = 0;

    protected:

        /**
        * @brief Template of Add Ref.
        * 
        * @tparam T The WebGPUObject.
        */
        template<typename T>
        static void AddRef(T*);

        /**
        * @brief Template of Release WebGPU Object.
        *
        * @tparam T The WebGPUObject.
        */
        template<typename T>
        static void Release(T*);

        /**
        * @brief Template of SetLabel WebGPU Object.
        *
        * @tparam T The WebGPUObject.
        * @param[in] label Label.
        */
        template<typename T>
        static void SetLabel(T*, const std::string& label) {}

    protected:

        /**
        * @brief Wait delegate to be down.
        *
        * @param[in] future WGPUFuture.
        */
        void Wait(const WGPUFuture& future);

    protected:

        /**
        * @brief The global WebGPUContext Referenced from WebGPURenderBackend.
        */
        WebGPUContext& m_Context;

    };

    template <typename T>
    void WebGPUObject::AddRef(T*)
    {
        NEPTUNE_CORE_WARN("WebGPUObject Not implement AddRef API.")
    }

    template <typename T>
    void WebGPUObject::Release(T*)
    {
        NEPTUNE_CORE_WARN("WebGPUObject Not implement Release API.")
    }
    
}

#endif