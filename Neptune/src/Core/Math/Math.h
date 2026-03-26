/**
* @file Math.h.
* @brief The Math Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Neptune {

    /**
    * @brief Decompose matrix to split SRT transform.
    * 
    * @param[in] transform Transform Matrix.
    * @param[in] outTranslation split translate.
    * @param[in] outRotation split rotation.
    * @param[in] outScale split scale.
    * 
    * @return Returns true if split succeed.
    */
    bool DecomposeTransform(
            const glm::mat4& transform,
            glm::vec3&       outTranslation,
            glm::vec3&       outRotation,
            glm::vec3&       outScale
    );

    /**
    * @brief Calculate Perspective Matrix.
    * 
    * @param[in] fov .
    * @param[in] nearPlane .
    * @param[in] farPlane .
    * @param[in] aspectRatio .
    * 
    * @return Returns Perspective Matrix.
    */
    glm::mat4 PerspectiveMatrix(float fov, float nearPlane, float farPlane, float aspectRatio);

    /**
    * @brief Calculate Orthographic Matrix.
    * 
    * @param[in] left .
    * @param[in] right .
    * @param[in] top .
    * @param[in] bottom .
    * @param[in] nearPlane .
    * @param[in] farPlane .
    * 
    * @return Returns Orthographic Matrix.
    */
    glm::mat4 OrthographicMatrix(float left, float right, float top, float bottom, float nearPlane, float farPlane);

    /**
    * @brief Calculate Perspective Matrix(reverse z version).
    * 
    * @param[in] fov .
    * @param[in] nearPlane .
    * @param[in] aspectRatio .
    * 
    * @return Returns Perspective Matrix(reverse z version).
    */
    glm::mat4 PerspectiveMatrixInverseZ(float fov, float nearPlane, float aspectRatio);

}