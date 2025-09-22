/**
* @file WorldMarkFlag.h.
* @brief The WorldMarkBit Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    enum class WorldMarkBit : uint32_t
    {
        DynamicScriptTick  = 0,
        DynamicScriptEvent = 1 << 0,

        Count              = 2,
    };

}
