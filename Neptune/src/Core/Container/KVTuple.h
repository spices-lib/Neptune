/**
* @file KVTuple.h.
* @brief The KVTuple Struct Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"

namespace Neptune::Container {

    /**
    * @brief Template of K(class) V(enum) tuple.
    * 
    * @tparam T_ Class.
    * @tparam E_ Enum.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    struct KVTuple 
    {
        using T = T_;

        static constexpr auto E = E_;
    };
    
}