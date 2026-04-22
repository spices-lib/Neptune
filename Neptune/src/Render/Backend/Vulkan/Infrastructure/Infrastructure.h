/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Backend/Common/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan {

    using namespace Common;
    
    using Context = Common::Infrastructure<EInfrastructure>::Context;
    
    using ContextAccessor = Common::Infrastructure<EInfrastructure>::ContextAccessor;
    
    /**
    * @brief Vulkan::Infrastructure Class.
    * This class defines the Vulkan::Infrastructure behaves.
    */
    class Infrastructure : public Common::Infrastructure<EInfrastructure>, public NonCopyable
    {
    public:

        using Super = Common::Infrastructure<EInfrastructure>;

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
        std::string ToString() const override;

    protected:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        explicit Infrastructure(Context& context, EInfrastructure e);

    };

}

#endif