/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "ContextAccessor.h"

namespace Neptune::Common {

    /**
    * @brief Common::Infrastructure Class.
    * This class defines the Common::Infrastructure behaves.
    * 
    * @tparam E EInfrastructure
    */
    template<typename E>
    class Infrastructure : public ContextAccessor<E>, public NonCopyable
    {
    public:

        using ContextAccessor = ContextAccessor<E>;

        using Context = Context<E>;

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
        virtual std::string ToString() const = 0;

    protected:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        explicit Infrastructure(Context& context, E e)
            : ContextAccessor(context)
            , m_EInfrastructure(e)
        {}

        /**
        * @brief Get EInfrastructure.
        *
        * @return Returns EInfrastructure.
        */
        const E& GetEInfrastructure() const { return m_EInfrastructure; }

    protected:

        E m_EInfrastructure; // @brief This EInfrastructure.

    };

}