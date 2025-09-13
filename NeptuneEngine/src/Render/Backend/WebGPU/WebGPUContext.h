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

    /**
    * @brief WebGPU object Type enum.
    */
    enum class EWebGPUObject : uint8_t
    {
        WebGPUInstance = 0,
        WebGPUSurface  = 1,
        WebGPUAdapter  = 2,
        WebGPUDevice   = 3,
        WebGPUQueue    = 4,

        MAX            = 5
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
        * @param[in] object WebGPU Object.
        */
        template<typename T>
        void Registry(SP<T> object);

        /**
        * @brief UnRegistry WebGPUObject from this context.
        * 
        * @param[in] object WebGPU Object.
        */
        template<typename T>
        void UnRegistry(SP<T> object);

        /**
        * @brief Get WebGPUObject from this context.
        *
        * @tparam T WebGPU Object.
        * 
        * @return Returns WebGPU Object.
        */
        template<typename T>
        T* Get();

    private:

        /**
        * @brief WebGPU Objects
        */
        std::array<SP<WebGPUObject>, static_cast<uint8_t>(EWebGPUObject::MAX)>  m_Objects;
    };

    template<typename T>
    void WebGPUContext::Registry(SP<T> object)
    {
        const auto position = static_cast<uint8_t>(object->GetType());

        m_Objects[position] = object;
    }

    template <typename T>
    void WebGPUContext::UnRegistry(SP<T> object)
    {
        const auto position = static_cast<uint8_t>(object->GetType());

        m_Objects[position] = nullptr;
    }

    template<typename T>
    T* WebGPUContext::Get()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        return static_cast<T*>(m_Objects[position].get());
    }

}

#endif