/**
* @file OrthographicCamera.cpp.
* @brief The OrthographicCamera Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "OrthographicCamera.h"
#include "Core/Math/Math.h"

namespace Neptune {

    OrthographicCamera::OrthographicCamera()
            : Camera(ProjectionType::Perspective)
    {}

    OrthographicCamera::OrthographicCamera(const OrthographicParam& param)
        : Camera(ProjectionType::Perspective)
        , m_OrthographicParam(param)
    {}

    glm::mat4 OrthographicCamera::GetPMatrix()
    {
        return OrthographicMatrix(
                m_OrthographicParam.left      ,
                m_OrthographicParam.right     ,
                m_OrthographicParam.top       ,
                m_OrthographicParam.bottom    ,
                m_OrthographicParam.nearPlane ,
                m_OrthographicParam.farPlane
        );
    }

    void OrthographicCamera::CalculatePMatrixReverseZ()
    {
        m_ProjectionMatrix = OrthographicMatrix(
                m_OrthographicParam.left      ,
                m_OrthographicParam.right     ,
                m_OrthographicParam.top       ,
                m_OrthographicParam.bottom    ,
                m_OrthographicParam.nearPlane ,
                m_OrthographicParam.farPlane
        );
    }
}
