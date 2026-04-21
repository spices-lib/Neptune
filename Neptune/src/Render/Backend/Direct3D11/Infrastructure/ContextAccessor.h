/**
* @file ContextAccessor.h.
* @brief The ContextAccessor Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"

namespace Neptune::Direct3D11 {

    class Context;
}

namespace Neptune::Direct3D11 {

    /**
    * @brief ContextAccessor Class.
    * This class defines the ContextAccessor behaves.
    */
    class ContextAccessor
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        ContextAccessor(Context& context) : m_Context(context) {}

        /**
        * @brief Destructor Function.
        */
        virtual ~ContextAccessor() = default;

    protected:

        /**
        * @brief Get Context.
        *
        * @return Returns Context.
        */
        constexpr Context& GetContext() const { return m_Context; }

    private:

        Context& m_Context; // @brief This Context.
    };
}

#endif