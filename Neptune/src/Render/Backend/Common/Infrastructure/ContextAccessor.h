/**
* @file ContextAccessor.h.
* @brief The ContextAccessor Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Common {

    template<typename E>
    class Context;
}

namespace Neptune::Common {

    /**
    * @brief ContextAccessor Class.
    * This class defines the ContextAccessor behaves.
    * 
    * @tparam E EInfrastructure
    */
    template<typename E>
    class ContextAccessor
    {
    public:

        using Context = Context<E>;

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