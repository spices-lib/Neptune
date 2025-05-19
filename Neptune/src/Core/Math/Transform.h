/**
* @file Transform.h.
* @brief The Transform Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Neptune {

    /**
    * @brief Wrapper of 3D Transform
    */
    struct Transform
    {
        glm::vec3 position{ 0.0f };  /* @brief Position Component. */
        glm::vec3 rotation{ 0.0f };  /* @brief Rotation Component. */
        glm::vec3 scale   { 1.0f };  /* @brief Scale    Component. */

        /**
        * @brief Get Model Matrix from this Transform.
        * @reutrn Returns this transform Matrix.
        */
        glm::mat4 ToMatrix();

        /**
        * @brief Get Rotation Matrix.
        * @param[in] rotation Rotation Component.
        * @return Returns Rotation Matrix.
        */
        static glm::mat4 GetRotationMatrix(const glm::vec3& rotation);

        /**
        * @brief Get Model Matrix from specific Transform.
        * @param[in] transform Specific transform.
        * @reutrn Returns specific transform Matrix.
        */
        static glm::mat4 ToMatrix(const Transform& transform);
    };
}