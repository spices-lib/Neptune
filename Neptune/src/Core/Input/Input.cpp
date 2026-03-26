/**
* @file Input.h.
* @brief The Input Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "Input.h"
#include "GLFW/InputImpl.h"

namespace Neptune {

    /**
    * @brief Instance a WindowsInput single instance.
    */
    std::unique_ptr<Input> Input::s_Instance = std::make_unique<GLFW::InputImpl>();

}