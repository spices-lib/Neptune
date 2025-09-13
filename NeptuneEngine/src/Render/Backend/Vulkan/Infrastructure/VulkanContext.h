/**
* @file VulkanContext.h.
* @brief The VulkanContext Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

    class VulkanInfrastructure;

    /**
    * @brief Vulkan Infrastructure Type enum.
    */
    enum class EVulkanInfrastructure : uint8_t
    {
        VulkanInstance         = 0,
        VulkanSurface          = 1,
        VulkanPhysicalSurface  = 2,
        VulkanDevice           = 3,
        VulkanQueue            = 4,
        VulkanMemoryAllocator  = 5,

        MAX                    = 6
    };

    /**
    * @brief This context contains all Vulkan object in used global.
    */
    class VulkanContext : NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        VulkanContext() = default;

        /**
        * @brief Destructor Function.
        */
        ~VulkanContext() override = default;

        /**
        * @brief Registry VulkanInfrastructure to this context.
        * 
        * @tparam T VulkanInfrastructure.
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
        * @brief Get VulkanInfrastructure from this context.
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
        std::array<SP<VulkanInfrastructure>, static_cast<uint8_t>(EVulkanInfrastructure::MAX)> m_Infrastructures;
    };

    template<typename T>
    void VulkanContext::Registry()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("VulkanInfrastructure already registried.")
        }

        m_Infrastructures[position] = CreateSP<T>(*this);
    }

    template <typename T>
    void VulkanContext::UnRegistry()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("VulkanInfrastructure is unregistry.")
            return;
        }

        m_Infrastructures[position].reset();
        m_Infrastructures[position] = nullptr;
    }

    template<typename T>
    T* VulkanContext::Get()
    {
        const auto position = static_cast<uint8_t>(T::Type);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("VulkanInfrastructure is unregistry.")
            return nullptr;
        }

        return static_cast<T*>(m_Infrastructures[position].get());
    }

}

#endif