/**
* @file Entity.cpp.
* @brief The Entity Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Entity.h"

namespace Neptune {

    void Entity::Destroy() const
    {
        m_Scene->Destroy(*this);
    }

    const UUID& Entity::GetUUID() const
    {
        return GetComponent<UUIDComponent>().GetUUID();
    }
}
