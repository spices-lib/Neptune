/**
* @file MouseButtonCodes.h.
* @brief The MouseButtonCodes Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune
{
    /**
    * @brief Helper Type instead uint16_t.
    */
    using MouseCode = uint16_t;

    namespace Mouse
    {

        /**
        * @brief Key Code enum same as glfw Mouse Code.
        */
        enum : MouseCode
        {
            Button0           = 0,
            Button1           = 1,
            Button2           = 2,
            Button3           = 3,
            Button4           = 4,
            Button5           = 5,
            Button6           = 6,
            Button7           = 7,

            ButtonLast        = Button7,
            ButtonLeft        = Button0,
            ButtonRight       = Button1,
            ButtonMiddle      = Button2

        };

        std::string ToString(MouseCode code)
        {
            switch (code)
            {
                case Button0           : return "ButtonLeft";
                case Button1           : return "ButtonRight";
                case Button2           : return "ButtonMiddle";
                case Button3           : return "Button3";
                case Button4           : return "Button4";
                case Button5           : return "Button5";
                case Button6           : return "Button6";
                case Button7           : return "ButtonLast";
            }

            return "Unknown Mouse Code";
        }
    }

}