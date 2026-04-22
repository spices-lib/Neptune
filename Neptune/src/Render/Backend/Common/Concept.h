#pragma once
#include "Core/Core.h"
#include <concepts>

namespace Neptune::Render::Common {
    
    template<typename B, typename D>
    concept IsBase = std::is_base_of_v<B, D>;

    template<typename T>
    concept IsUnit = true;
    
}