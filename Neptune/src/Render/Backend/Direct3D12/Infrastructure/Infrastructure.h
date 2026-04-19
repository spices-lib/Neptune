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
#include "Render/Backend/Direct3D12/Core.h"
#include "ContextAccessor.h"

namespace Neptune::Direct3D12 {

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