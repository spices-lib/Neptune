/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune::WebGPU {

    class InfrastructureBase;

    /**
    * @brief WebGPU EInfrastructure Type enum.
    */
    enum class EInfrastructure : uint8_t
    {
        Instance,
        Surface,
        Adapter,
        Device,
        Queue,

        MAX
    };

    /**
    * @brief This context contains all WebGPU object in used global.
    */
    class Context : NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Context() = default;

        /**
        * @brief Destructor Function.
        */
        ~Context() override = default;

        /**
        * @brief Registry Infrastructure to this context.
        */
        template<typename T>
        void Registry();

        /**
        * @brief UnRegistry Infrastructure from this context.
        */
        template<typename T>
        void UnRegistry();

        /**
        * @brief Get Infrastructure from this context.
        *
        * @tparam T WebGPU Infrastructure.
        * 
        * @return Returns WebGPU Infrastructure.
        */
        template<typename T>
        T* Get();

    private:

        /**
        * @brief WebGPU Infrastructure
        */
        std::array<SP<InfrastructureBase>, static_cast<uint8_t>(EInfrastructure::MAX)> m_Infrastructures;
    };

    template<typename T>
    void Context::Registry()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(T::Type);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("WebGPU Infrastructure already registried.")
        }

        m_Infrastructures[position] = CreateSP<T>(*this);
    }

    template <typename T>
    void Context::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("WebGPU Infrastructure is unregistry.")
            return;
        }

        m_Infrastructures[position].reset();
        m_Infrastructures[position] = nullptr;
    }

    template<typename T>
    T* Context::Get()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("WebGPU Infrastructure is unregistry.")
            return nullptr;
        }

        return static_cast<T*>(m_Infrastructures[position].get());
    }

}

#endif