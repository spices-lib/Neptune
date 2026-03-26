#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "Render/Backend/Vulkan/Core.h"
#include "ContextAccessor.h"

namespace Neptune::Vulkan {

    class Infrastructure : public ContextAccessor, public NonCopyable
    {
    public:

        explicit Infrastructure(Context& context, EInfrastructure e);

        ~Infrastructure() override = default;

    public:

        std::string ToString() const;

    protected:

        const EInfrastructure& GetInfrastructure() const { return m_EInfrastructure; }

    private:

        EInfrastructure m_EInfrastructure;

    };

}