#pragma once
#include "Core/Core.h"
#include <concepts>

namespace Neptune::Render::Common {

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
    * @brief Concept: Is Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsEnum = std::is_enum_v<T>;
    
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
    
    /**
    * @brief Concept: Is Unit Handle.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnitHandle = IsPointer<T> || IsIntegral<T>;
    
    /**
    * @brief Concept: Is Unit EUnit.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnitEUnit = IsEnum<T> || IsIntegral<T>;
    
    /**
    * @brief Concept: Is Unit.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnit = requires(T t) {
        typename T::Handle;
        typename decltype(T::E_);
        IsUnitHandle<typename T::Handle>;
        IsUnitEUnit<decltype(T::E_)>;
    };
    
    /**
    * @brief Concept: Is ContextAccessor.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsContextAccessor = requires(T t) {
        typename T::Context;
    };
    
    /**
    * @brief Concept: Is Infrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsInfrastructure = requires(T t) {
        typename T::ContextAccessor;
        typename T::Context;
    };
    
    /**
    * @brief Concept: Is IInfrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIInfrastructure = requires(T t) {
        typename T::T;
        typename decltype(T::E);
        IsInfrastructure<typename T::T>;
        IsEnum<decltype(T::E)>;
    };
    
}