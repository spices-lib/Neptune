#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

enum class slice_type_e : uint8_t
{
    P  = 0,
    B  = 1,
    I  = 2,
    SP = 3,
    SI = 4,
};

#endif