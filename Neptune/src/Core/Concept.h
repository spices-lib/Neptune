/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include <concepts>

namespace Neptune {
    
    /**
    * @brief Concept: Is Base of.
    * 
    * @tparam B Base Class.
    * @tparam D Derived Class.
    */
    template<typename B, typename D>
    concept IsBase = std::is_base_of_v<B, D>;

    /**
    * @brief Concept: Is Same as.
    * 
    * @tparam T1 One Class.
    * @tparam T2 Another Class.
    */
    template<typename T1, typename T2>
    concept IsSame = std::is_same_v<T1, T2>;
    
    /**
    * @brief Concept: Is Convertible to.
    * 
    * @tparam T1 One Class.
    * @tparam T2 Another Class.
    */
    template<typename T1, typename T2>
    concept IsConvertible = std::is_convertible_v<T1, T2>;
    
    /**
    * @brief Concept: Is Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsEnum = std::is_enum_v<T> && requires {
        { T::Count } -> std::convertible_to<T>;
    };
    
    /**
    * @brief Concept: Is Empty Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsEmptyEnum = IsEnum<T> && requires {
        { T::Count } -> std::convertible_to<T>;
        requires std::bool_constant<static_cast<uint32_t>(T::Count) == 0>::value;
    };
    
    /**
    * @brief Concept: Is Not Empty Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsNotEmptyEnum = !IsEmptyEnum<T>;
    
    /**
    * @brief Concept: Is Pointer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsPointer = std::is_pointer_v<T>;
    
    /**
    * @brief Concept: Is Integral.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIntegral = std::is_integral_v<T>;
    
}