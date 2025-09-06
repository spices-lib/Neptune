/**
* @file Camera.cpp.
* @brief The Camera Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Camera.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

namespace Neptune {

    SP<Camera> Camera::CreatePerspective(const PerspectiveParam& param)
    {
        return CreateSP<PerspectiveCamera>(param);
    }

    SP<Camera> Camera::CreateOrthographic(const OrthographicParam& param)
    {
        return CreateSP<OrthographicCamera>(param);
    }

    const glm::mat4& Camera::GetPMatrixReverseZ()
    {
        CalculatePMatrixReverseZ();
        return m_ProjectionMatrix;
    }
}
