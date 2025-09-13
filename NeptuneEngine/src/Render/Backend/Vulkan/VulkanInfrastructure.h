/**
* @file WebGPUUtils.h.
* @brief The WebGPUObject Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "VulkanContext.h"
#include "VulkanUtils.h"

namespace Neptune {

    /**
    * @brief VulkanInfrastructure Class.
    * This class defines the basic behaves of VulkanInfrastructure.
    * When we create an new VulkanInfrastructure, we need inherit from this.
    */
    class VulkanInfrastructure : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global VulkanContext.
        */
        explicit VulkanInfrastructure(VulkanContext& context);

        /**
        * @brief Destructor Function.
        */
        ~VulkanInfrastructure() override;

    protected:

        /**
        * @brief Template of Destroy WebGPU Object.
        *
        * @tparam T The WebGPUObject.
        */
        template<typename T>
        static void Destroy(T*);

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
        * @brief The global VulkanContext Referenced from VulkanRenderBackend.
        */
        VulkanContext& m_Context;

    };

    template <typename T>
    void VulkanInfrastructure::Destroy(T*)
    {
        NEPTUNE_CORE_WARN("VulkanInfrastructure Not implement Destroy API.")
    }

}

#endif