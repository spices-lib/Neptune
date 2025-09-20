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
        NEPTUNE_PROFILE_ZONE

        m_Scene->Destroy(*this);
    }

    const UUID& Entity::GetUUID() const
    {
        NEPTUNE_PROFILE_ZONE

        return GetComponent<UUIDComponent>().GetUUID();
    }
}
