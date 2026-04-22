/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

#include <array>

namespace Neptune::Common {

    template<typename E>
    class Infrastructure;
}

namespace Neptune::Common {

    /**
    * @brief Template of Infrastructure Class Definitions.
    * 
    * @tparam T_ Infrastructure Class.
    * @tparam E_ EInfrastructure.
    */
    template<typename T_, auto E_>
	struct InfrastructureClass
	{
		using T = T_;

        static constexpr auto E = E_;
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
    * 
    * @tparam E EInfrastructure.
    */
    template<typename E>
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

        std::array<SP<Infrastructure<E>>, static_cast<uint8_t>(E::Count)> m_Infrastructures; // @brief Container of Infrastructure.

    };

    template<typename E>
    template<typename I, typename... Args>
    inline void Context<E>::Registry(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Infrastructure Already Registered.")

            return;
        }

        m_Infrastructures[position] = InfrastructureFactory<typename I::T>(*this, I::E, std::forward<Args>(args)...);
    }

    template<typename E>
    template<typename I>
    inline void Context<E>::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Infrastructure is not registered yet, can not be unregister.")

            return;
        }

        m_Infrastructures[position].reset();
    }

    template<typename E>
    inline void Context<E>::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        for (int i = static_cast<int>(E::Count) - 1; i >= 0; --i)
        {
            if (!m_Infrastructures[i])
            {
                NEPTUNE_CORE_ERROR("Infrastructure is not registered yet, can not be unregister.")

                continue;
            }

            m_Infrastructures[i].reset();
        }
    }

    template<typename E>
    template<typename I>
    I::T* Context<E>::Get()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Infrastructure is not registered yet, can not be got.")

            return nullptr;
        }

        return std::dynamic_pointer_cast<typename I::T>(m_Infrastructures[position]).get();
    }

    template<typename E>
    template<typename I>
    bool Context<E>::Has() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }

}