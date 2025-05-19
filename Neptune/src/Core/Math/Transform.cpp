/**
* @file Transform.h.
* @brief The Transform Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Transform.h"

namespace Neptune {

    glm::mat4 Transform::ToMatrix()
    {
        return std::move(
            glm::translate(glm::mat4(1.0f), position) *
            GetRotationMatrix(rotation) *
            glm::scale(glm::mat4(1.0f), scale)
        );
    }

    glm::mat4 Transform::GetRotationMatrix(const glm::vec3& rotation)
    {
        return
        std::move(
            glm::toMat4(
            glm::quat({
                glm::radians(rotation.x),
                glm::radians(rotation.y),
                glm::radians(rotation.z)
            })
        ));
    }

    glm::mat4 Transform::ToMatrix(const Transform& transform)
    {
        return std::move(
            glm::translate(glm::mat4(1.0f), transform.position) *
            GetRotationMatrix(transform.rotation) *
            glm::scale(glm::mat4(1.0f), transform.scale)
        );
    }
}