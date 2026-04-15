/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "Render/Backend/Vulkan/Core.h"
#include "ContextAccessor.h"

namespace Neptune::Vulkan {

    /**
    * @brief Vulkan::Infrastructure Class.
    * This class defines the Vulkan::Infrastructure behaves.
    */
    class Infrastructure : public ContextAccessor, public NonCopyable
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~Infrastructure() override = default;

    public:

        /**
        * @brief Turn EInfrastructure to string.
        * 
        * @return Returns string EInfrastructure.
        */
        std::string ToString() const;

    protected:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        explicit Infrastructure(Context& context, EInfrastructure e);

        /**
        * @brief Get EInfrastructure.
        *
        * @return Returns EInfrastructure.
        */
        const EInfrastructure& GetEInfrastructure() const { return m_EInfrastructure; }

    private:

        EInfrastructure m_EInfrastructure; // @brief This EInfrastructure.

    };

}

#endif