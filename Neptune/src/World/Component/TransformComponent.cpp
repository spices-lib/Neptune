/**
* @file TransformComponent.cpp.
* @brief The TransformComponent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "TransformComponent.h"

namespace Neptune {

    TransformComponent::TransformComponent()
            : Component()
    {
        NEPTUNE_PROFILE_ZONE

        SetPosition({ 0.0f, 0.0f, 0.0f });
        SetRotation({ 0.0f, 0.0f, 0.0f });
        SetScale({ 1.0f, 1.0f, 1.0f });
    }

    glm::mat4 TransformComponent::GetRotateMatrix() const
    {
        NEPTUNE_PROFILE_ZONE

        return Transform::GetRotationMatrix(m_Transform.rotation);
    }

    void TransformComponent::ClearMarkerWithBits(TransformComponentFlags flags)
    {
        NEPTUNE_PROFILE_ZONE

        if (m_Marker & flags)
        {
            m_Marker ^= flags;
        }
    }

    void TransformComponent::CalMatrix()
    {
        NEPTUNE_PROFILE_ZONE

        m_ModelMatrix = m_Transform.ToMatrix();
    }
}
