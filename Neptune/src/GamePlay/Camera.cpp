/**
* @file Camera.cpp.
* @brief The Camera Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Camera.h"
#include "Core/Math/Math.h"
#include "Render/FrameInfo.h"

namespace Neptune {

	void Camera::SetPerspective(float fov, float nearPlane, float aspectRatio)
	{
		NEPTUNE_PROFILE_ZONE;
		
		m_ProjectionType = ProjectionType::Perspective;

		m_PerspectiveParam.fov         = fov;
		m_PerspectiveParam.nearPlane   = nearPlane;
		m_PerspectiveParam.aspectRatio = aspectRatio;
	}

	void Camera::SetPerspective(float aspectRatio)
	{
		NEPTUNE_PROFILE_ZONE;
		
		m_ProjectionType = ProjectionType::Perspective;
		
		SetPerspective(m_PerspectiveParam.fov, m_PerspectiveParam.nearPlane, aspectRatio);
	}

	void Camera::SetOrthographic(float left, float right, float top, float bottom, float nearPlane, float farPlane)
	{
		NEPTUNE_PROFILE_ZONE;
		
		m_ProjectionType = ProjectionType::Orthographic;

		m_OrthographicParam.left        = left;
		m_OrthographicParam.right       = right;
		m_OrthographicParam.top         = top;
		m_OrthographicParam.bottom      = bottom;
		m_OrthographicParam.nearPlane   = nearPlane;
		m_OrthographicParam.farPlane    = farPlane;
	}

	void Camera::ResetStableFrames()
	{
		NEPTUNE_PROFILE_ZONE;
		
		if (FrameInfo::Get().m_RendererType == RendererType::Rasterization) return;
		
		if (m_StableFrames > 100)
		{
		}

		m_StableFrames = 0;
	}

	const glm::mat4 Camera::GetPMatrix() const
	{
		NEPTUNE_PROFILE_ZONE;
		
		switch (m_ProjectionType)
		{
		case ProjectionType::Perspective:
			return PerspectiveMatrix(
				m_PerspectiveParam.fov        , 
				m_PerspectiveParam.nearPlane  ,
				100000000.0f,
				m_PerspectiveParam.aspectRatio
			);
		case ProjectionType::Orthographic:
			return OtrhographicMatrix(
				m_OrthographicParam.left      ,
				m_OrthographicParam.right     ,
				m_OrthographicParam.top       ,
				m_OrthographicParam.bottom    ,
				m_OrthographicParam.nearPlane ,
				m_OrthographicParam.farPlane
			);
		}

		return glm::mat4(1.0f);
	}

	void Camera::CalculatePMatrixReverseZ()
	{
		NEPTUNE_PROFILE_ZONE;
		
		switch (m_ProjectionType)
		{
		case ProjectionType::Perspective:
			m_ProjectionMatrix = PerspectiveMatrixInverseZ(
				m_PerspectiveParam.fov        , 
				m_PerspectiveParam.nearPlane  ,
				m_PerspectiveParam.aspectRatio
			);
			break;
		case ProjectionType::Orthographic:
			m_ProjectionMatrix = OtrhographicMatrix(
				m_OrthographicParam.left      ,
				m_OrthographicParam.right     ,
				m_OrthographicParam.top       ,
				m_OrthographicParam.bottom    ,
				m_OrthographicParam.nearPlane ,
				m_OrthographicParam.farPlane
			);
			break;
		}
	}
}
