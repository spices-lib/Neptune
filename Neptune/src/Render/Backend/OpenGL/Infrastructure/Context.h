/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"

#include <array>

namespace Neptune::OpenGL {

    class Infrastructure;

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        DebugUtilsObject = 0,                // @brief Label/Name Functors.

        GraphicFence,                        // @brief Main Thread Graphic Fence.

        Count
    };

    /**
    * @brief Template of Infrastructure Class Definitions.
    * 
    * @tparam T_ Infrastructure Class.
    * @tparam E_ EInfrastructure.
    */
    template<typename T_, EInfrastructure E_>
	struct InfrastructureClass
	{
		using T = T_;
        static constexpr EInfrastructure E = E_;
	};

    /**
    * @brief Infrastructure Factory.
    *
    * @tparam T Specification of Infrastructure.
    * @param[in] args Infrastructure Params.
    * 
    * @return Returns Infrastructure.
    */
    template<typename T, typename... Args>
    static SP<T> InfrastructureFactory(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE
        
        if constexpr (requires(Args... args) {
            { T::Create(std::forward<Args>(args)...) } -> std::same_as<SP<T>>;
        })
        {
            // Factory Version
            return T::Create(std::forward<Args>(args)...);
        }
        else
        {
            // Directory Version
            return CreateSP<T>(std::forward<Args>(args)...);
        }
    }
    
    /**
    * @brief RenderBackend Context.
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
        * @brief Registry Infrastructure.
        *
        * @tparam I Infrastructure Definitions.
        * @param[in] args Infrastructure Construct Params.
        */
        template<typename I, typename... Args>
        void Registry(Args&&... args);

        /**
        * @brief Unregister Infrastructure.
        *
        * @tparam I Infrastructure Definitions.
        */
        template<typename I>
        void UnRegistry();

        /**
        * @brief Unregister All Infrastructure.
        */
        void UnRegistry();

        /**
        * @brief Get registry Infrastructure.
        *
        * @tparam I Infrastructure Definitions.
        * 
        * @return Returns registry Infrastructure.
        */
        template<typename I>
        I::T* Get();

        /**
        * @brief Is Infrastructure registry.
        *
        * @tparam I Infrastructure Definitions.
        *
        * @return Returns true if registry.
        */
        template<typename I>
        bool Has() const;

    private:

        std::array<SP<Infrastructure>, static_cast<uint8_t>(EInfrastructure::Count)> m_Infrastructures; // @brief Container of Infrastructure.

    };

    template<typename I, typename... Args>
    inline void Context::Registry(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("OpenGL Infrastructure Already Registered.")

            return;
        }

        m_Infrastructures[position] = InfrastructureFactory<typename I::T>(*this, I::E, std::forward<Args>(args)...);
    }

    template <typename I>
    inline void Context::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("OpenGL Infrastructure is not registered yet, can not be unregisted.")

            return;
        }

        m_Infrastructures[position].reset();
    }

    inline void Context::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        for (int i = static_cast<int>(EInfrastructure::Count) - 1; i >= 0; i--)
        {
            if (!m_Infrastructures[i])
            {
                NEPTUNE_CORE_ERROR("OpenGL Infrastructure is not registered yet, can not be unregisted.")

                continue;
            }

            m_Infrastructures[i].reset();
        }
    }

    template<typename I>
    I::T* Context::Get()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("OpenGL Infrastructure is not registered yet, can not be got.")

            return nullptr;
        }

        return std::dynamic_pointer_cast<typename I::T>(m_Infrastructures[position]).get();
    }

    template<typename I>
    bool Context::Has() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }

}

#endif