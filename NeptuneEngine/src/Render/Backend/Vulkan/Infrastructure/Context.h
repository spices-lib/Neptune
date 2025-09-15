/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune::Vulkan {

    class Infrastructure;

    /**
    * @brief Vulkan Infrastructure Type enum.
    */
    enum class EInfrastructure : uint8_t
    {
        Instance,
        Functions,
        Surface,
        PhysicalSurface,
        Device,
        ThreadQueue,
        MemoryAllocator,
        SwapChain,
        CommandPool,
        DescriptorPool,

        MAX
    };

    /**
    * @brief This context contains all Vulkan Infrastructure in used global.
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
        * @brief Registry Vulkan Infrastructure to this context.
        * 
        * @tparam T Vulkan Infrastructure.
        */
        template<typename T>
        void Registry();

        /**
        * @brief UnRegistry VulkanInfrastructure from this context.
        * 
        * @tparam T VulkanInfrastructure.
        */
        template<typename T>
        void UnRegistry();

        /**
        * @brief Get Vulkan Infrastructure from this context.
        *
        * @tparam T Vulkan Infrastructure.
        *
        * @return Returns Vulkan Infrastructure.
        */
        template<typename T>
        T* Get();

    private:

        /**
        * @brief Vulkan Infrastructures
        */
        std::array<SP<Infrastructure>, static_cast<uint8_t>(EInfrastructure::MAX)> m_Infrastructures;
    };

    template<typename T>
    void Context::Registry()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure already registried.")
        }

        m_Infrastructures[position] = CreateSP<T>(*this);
    }

    template <typename T>
    void Context::UnRegistry()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure is unregistry.")
            return;
        }

        m_Infrastructures[position].reset();
        m_Infrastructures[position] = nullptr;
    }

    template<typename T>
    T* Context::Get()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure is unregistry.")
            return nullptr;
        }

        return static_cast<T*>(m_Infrastructures[position].get());
    }

}

#endif