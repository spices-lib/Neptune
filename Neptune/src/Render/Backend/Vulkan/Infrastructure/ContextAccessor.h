#pragma once
#include "Core/Core.h"
#include <vulkan/vulkan.h>

namespace Neptune::Vulkan {
    class Context;
}

namespace Neptune::Vulkan {

    class ContextAccessor
    {
    public:

        ContextAccessor(Context& context) : m_Context(context) {}

        virtual ~ContextAccessor() = default;

    protected:

        constexpr Context& GetContext() const { return m_Context; }
        
        VkDevice GetDevice() const;

    private:

        Context& m_Context;
    };
}
