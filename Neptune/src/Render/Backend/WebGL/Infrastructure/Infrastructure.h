/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Backend/Common/Infrastructure/Infrastructure.h"

namespace Neptune::WebGL {

    using namespace Render::Common;

    using CommonInfrastructure = Render::Common::Infrastructure<EInfrastructure>;

    using Context = CommonInfrastructure::Context;

    using ContextAccessor = CommonInfrastructure::ContextAccessor;

    /**
    * @brief WebGL::Infrastructure Class.
    * This class defines the WebGL::Infrastructure behaves.
    */
    class Infrastructure : public CommonInfrastructure, public NonCopyable
    {
    public:

        using Super = CommonInfrastructure;

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