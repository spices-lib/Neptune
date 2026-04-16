/**
* @file ContextAccessor.h.
* @brief The ContextAccessor Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"

namespace Neptune::OpenGL {

    class Context;
}

namespace Neptune::OpenGL {

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