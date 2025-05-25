/**
* @file PerspectiveCamera.h.
* @brief The PerspectiveCamera Class Definitions.
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
    class PerspectiveCamera : public Camera
    {
    public:

        /**
        * @brief Constructor Function.
        */
        PerspectiveCamera();

        /**
        * @brief Constructor Function.
        * @param[in] param PerspectiveParam.
        */
        PerspectiveCamera(const PerspectiveParam& param);

        /**
        * @brief Destructor Function.
        */
        virtual ~PerspectiveCamera() = default;

        /**
        * @brief Get camera projection matrix.
        * @return Returns the camera projection matrix.
        * @note only use in ImguiGizmos.
        */
        virtual glm::mat4 GetPMatrix() override;

        /**
        * @brief Get this camera parameter.
        * @return Returns this camera parameter.
        */
        PerspectiveParam& GetParam() { return m_PerspectiveParam; }

        /**
        * @brief Get this camera parameter.
        * @return Returns this camera parameter.
        */
        const PerspectiveParam& GetParam() const { return m_PerspectiveParam; }

    private:

        /**
        * @brief Calculate Projection Matrix by parameter.
        */
        virtual void CalculatePMatrixReverseZ() override;

    private:

        /**
        * @brief Camera PerspectiveParam.
        */
        PerspectiveParam m_PerspectiveParam;
    };
}