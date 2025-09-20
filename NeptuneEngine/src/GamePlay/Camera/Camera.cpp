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
        NEPTUNE_PROFILE_ZONE

        return CreateSP<PerspectiveCamera>(param);
    }

    SP<Camera> Camera::CreateOrthographic(const OrthographicParam& param)
    {
        NEPTUNE_PROFILE_ZONE

        return CreateSP<OrthographicCamera>(param);
    }

    const glm::mat4& Camera::GetPMatrixReverseZ()
    {
        NEPTUNE_PROFILE_ZONE

        CalculatePMatrixReverseZ();
        return m_ProjectionMatrix;
    }
}
