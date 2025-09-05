/**
* @file GLFWInput.h.
* @brief The GLFWInput Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Input/Input.h"

namespace Neptune {

    /**
    * @brief This Class Is gltf Specific Input Class.
    */
    class GLFWInput : public Input
    {
    protected:

        /**
        * @brief Query If given Key is Pressed.
        * 
        * @param[in] keycode In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        bool IsKeyPressedImpl(const int& keycode) override;

        /**
        * @brief Query If given Mouse Button is Pressed.
        * 
        * @param[in] button In Mouse Button.
        * 
        * @return Returns true if given Key is Pressed.
        */
        bool IsMouseButtonPressedImpl(const int& button) override;

        /**
        * @brief Query Mouse Position in Windows.
        * 
        * @return Returns the pair of Mouse Position in Windows.
        */
        std::pair<float, float> GetMousePositionImpl() override;

        /**
        * @brief Query Mouse X Position in Windows.
        * 
        * @return Returns the Mouse X Position in Windows.
        */
        float GetMouseXImpl() override;

        /**
        * @brief Query Mouse Y Position in Windows.
        * 
        * @return Returns the Mouse Y Position in Windows.
        */
        float GetMouseYImpl() override;
    };
}