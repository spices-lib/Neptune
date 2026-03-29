/**
* @file ContextAccessor.h.
* @brief The ContextAccessor Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <vulkan/vulkan.h>

namespace Neptune::Vulkan {
    class Context;
}

namespace Neptune::Vulkan {

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
        
        /**
        * @brief Get Logical Device Handle.
        *
        * @return Returns Logical Device Handle.
        */
        VkDevice GetDevice() const;

    private:

        Context& m_Context; // @brief This Context.
    };
}
