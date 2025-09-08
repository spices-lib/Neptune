/**
* @file Component.cpp.
* @brief The Component Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Component.h"

namespace Neptune {

    void Component::OnComponentAttached(uint32_t entity)
    {
        m_Owner = entity;
    }

    void Component::OnComponentDetached()
    {}
}