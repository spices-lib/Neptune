/**
* @file Camera.h.
* @brief The Camera Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Neptune {

    /**
    * @brief This Struct defines camera projection type.
    */
    enum class ProjectionType
    {
        Perspective  = 0,
        Orthographic = 1,
    };

    /**
	* @brief when ProjectionType==Orthographic, use this.
	*/
    struct OrthographicParam
    {
        float left      = -10.0f;            /* @brief Left Plane of Camera.               */
        float right     = 10.0f;             /* @brief Right Plane of Camera.              */
        float top       = 10.0f;             /* @brief Top Plane of Camera.                */
        float bottom    = -10.0f;            /* @brief Bottom Plane of Camera.             */
        float nearPlane = 0.01f;             /* @brief Near Plane of Camera.               */
        float farPlane  = 1000.0f;           /* @brief Far Plane of Camera.                */
    };

    /**
    * @brief when ProjectionType==Perspective, use this.
    */
    struct PerspectiveParam
    {
        float fov           = 45.0f;         /* @brief Use degree as well, While PerspectiveMatrix() turn it to radians for calculate. */
        float nearPlane     = 0.01f;         /* @brief Near Plane of Camera.               */
        float aspectRatio   = 1.777f;        /* @brief Viewport Width / Height of Camera.  */
    };

    /**
    * @brief Camera Class.
    * This class just encapsulate Projection Matrix.
    */
    class Camera
    {
    public:

        /**
        * @brief Create Perspective Camera.
        * 
        * @param[in] param PerspectiveParam
        * 
        * @return Returns Perspective Camera.
        */
        static SP<Camera> CreatePerspective(const PerspectiveParam& param);

        /**
        * @brief Create Orthographic Camera.
        * 
        * @param[in] param OrthographicParam
        * 
        * @return Returns Orthographic Camera.
        */
        static SP<Camera> CreateOrthographic(const OrthographicParam& param);

    public:

        /**
        * @brief Constructor Function.
        */
        Camera() = default;

        /**
        * @brief Constructor Function.
        * 
        * @param[in] type ProjectionType.
        */
        Camera(ProjectionType type)
            : m_ProjectionType(type)
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Camera() = default;

        /**
        * @brief Get camera reverse z projection matrix.
        * 
        * @return Returns the camera projection matrix.
        */
        const glm::mat4& GetPMatrixReverseZ();

        /**
        * @brief Get camera projection matrix.
        * 
        * @return Returns the camera projection matrix.
        * 
        * @note only use in ImguiGizmos.
        */
        virtual glm::mat4 GetPMatrix() = 0;

        /**
        * @brief Get camera projection type.
        * 
        * @return Returns the camera projection type.
        */
        const ProjectionType& GetProjectionType() const { return m_ProjectionType; }

    private:

        /**
        * @brief Calculate Projection Matrix by parameter.
        */
        virtual void CalculatePMatrixReverseZ() = 0;

    protected:

        /**
        * @brief ProjectionMatrix.
        * Init with identity Matrix.
        */
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

        /**
        * @breif ProjectionType.
        * Init with Perspective.
        */
        ProjectionType m_ProjectionType = ProjectionType::Perspective;
    };
}