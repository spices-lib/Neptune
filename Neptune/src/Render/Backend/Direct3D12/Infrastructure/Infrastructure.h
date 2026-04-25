/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Backend/Common/Infrastructure/Infrastructure.h"

namespace Neptune::Direct3D12 {

    using namespace Render::Common;

    using CommonInfrastructure = Render::Common::Infrastructure<EInfrastructure>;

    using Context = CommonInfrastructure::Context;

    using ContextAccessor = CommonInfrastructure::ContextAccessor;

    /**
    * @brief Direct3D12::Infrastructure Class.
    * This class defines the Direct3D12::Infrastructure behaves.
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