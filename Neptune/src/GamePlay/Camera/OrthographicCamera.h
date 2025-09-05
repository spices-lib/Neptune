/**
* @file OrthographicCamera.h.
* @brief The OrthographicCamera Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Camera.h"

namespace Neptune {

    /**
    * @brief Camera Class.
    * This class just encapsulate projection Matrix.
    */
    class OrthographicCamera : public Camera
    {
    public:

        /**
        * @brief Constructor Function.
        */
        OrthographicCamera();

        /**
        * @brief Constructor Function.
        * @param[in] param OrthographicParam.
        */
        OrthographicCamera(const OrthographicParam& param);

        /**
        * @brief Destructor Function.
        */
        ~OrthographicCamera() override = default;

        /**
        * @brief Get camera projection matrix.
        * 
        * @return Returns the camera projection matrix.
        * 
        * @note only use in ImguiGizmos.
        */
        glm::mat4 GetPMatrix() override;

        /**
        * @brief Get this camera parameter.
        * 
        * @return Returns this camera parameter.
        */
        OrthographicParam& GetParam() { return m_OrthographicParam; }

        /**
        * @brief Get this camera parameter.
        * 
        * @return Returns this camera parameter.
        */
        const OrthographicParam& GetParam() const { return m_OrthographicParam; }

    private:

        /**
        * @brief Calculate Projection Matrix by parameter.
        */
        void CalculatePMatrixReverseZ() override;

    private:

        /**
        * @brief Camera OrthographicParam.
        */
        OrthographicParam m_OrthographicParam;
    };
}