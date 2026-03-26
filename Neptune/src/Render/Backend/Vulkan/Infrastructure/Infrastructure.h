/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "Render/Backend/Vulkan/Utils.h"

namespace Neptune::Vulkan {

    /**
    * @brief Infrastructure Class.
    * This class defines the basic behaves of Infrastructure.
    * When we create an new Infrastructure, we need inherit from this.
    */
    class Infrastructure : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global VulkanContext.
        */
        explicit Infrastructure(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~Infrastructure() override;

    protected:

        /**
        * @brief Template of Destroy Vulkan Infrastructure.
        *
        * @tparam T The Vulkan Infrastructure.
        */
        template<typename T>
        static void Destroy(T*);

        /**
        * @brief Template of SetLabel Vulkan Infrastructure.
        *
        * @tparam T The Vulkan Infrastructure.
        * @param[in] label Label.
        */
        template<typename T>
        static void SetLabel(T*, const std::string& label) {}

    protected:

        /**
        * @brief The global Vulkan Context Referenced from Vulkan RenderBackend.
        */
        Context& m_Context;

    };

    template <typename T>
    void Infrastructure::Destroy(T*)
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_CORE_WARN("Vulkan Infrastructure Not implement Destroy API.")
    }

}

#endif