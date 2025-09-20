/**
* @file PerspectiveCamera.cpp.
* @brief The PerspectiveCamera Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "PerspectiveCamera.h"
#include "Core/Math/Math.h"

namespace Neptune {

    PerspectiveCamera::PerspectiveCamera()
        : Camera(ProjectionType::Perspective)
    {}

    PerspectiveCamera::PerspectiveCamera(const PerspectiveParam& param)
        : Camera(ProjectionType::Perspective)
        , m_PerspectiveParam(param)
    {}

    glm::mat4 PerspectiveCamera::GetPMatrix()
    {
        NEPTUNE_PROFILE_ZONE

        return PerspectiveMatrix(
                m_PerspectiveParam.fov        ,
                m_PerspectiveParam.nearPlane  ,
                100000000.0f,
                m_PerspectiveParam.aspectRatio
        );
    }

    void PerspectiveCamera::CalculatePMatrixReverseZ()
    {
        NEPTUNE_PROFILE_ZONE

        m_ProjectionMatrix = PerspectiveMatrixInverseZ(
                m_PerspectiveParam.fov        ,
                m_PerspectiveParam.nearPlane  ,
                m_PerspectiveParam.aspectRatio
        );
    }
}
