/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Slate Backend.
    */
    enum class SlateBackendEnum : uint8_t
    {
        None = 0,
        ImGui,

        Count
    };

}