/**
* @file Component.cpp.
* @brief The Component Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Component.h"

namespace Neptune {

    void Component::OnComponentAdded(uint32_t entity)
    {
        m_Owner = entity;
    }
}