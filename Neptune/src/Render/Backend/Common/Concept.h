/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"

namespace Neptune::Render::Common {
    
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
    concept IsUnitEUnit = std::is_enum_v<T> || IsIntegral<T>;
    
    /**
    * @brief Concept: Is Unit.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnit = requires(T t) {
        typename T::Handle;
        t.E_;
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
        t.E;
        IsInfrastructure<typename T::T>;
        IsEnum<decltype(T::E)>;
    };
    
}