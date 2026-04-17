/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of System.
    */
    enum class ESystem : uint8_t
    {
        Logical = 0,
        Render,
        RHI,

        Count
    };

}