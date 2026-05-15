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

namespace Neptune::OpenGL {

    using namespace Render::Common;

    using CommonInfrastructure = Render::Common::Infrastructure<EInfrastructure>;

    using Context = CommonInfrastructure::Context;

    using ContextAccessor = CommonInfrastructure::ContextAccessor;

    /**
    * @brief OpenGL::Infrastructure Class.
    * This class defines the OpenGL::Infrastructure behaves.
    */
    class Infrastructure : public CommonInfrastructure
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