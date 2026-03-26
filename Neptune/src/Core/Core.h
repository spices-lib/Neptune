/**
* @file Core.h.
* @brief Neptune Core Macro.
* @author Spices.
*/

#pragma once
#include "Log/Log.h"
#include "Debugger/Profiler/Profiler.h"

#include <forward_list>

namespace Neptune {

/**
* @brief Assert macro.
* @todo better Assert System.
*/
#define ASSERT(expr)                                                                                          \
    {                                                                                                         \
        if (expr) {}                                                                                          \
        else                                                                                                  \
        {                                                                                                     \
            std::stringstream ss;                                                                             \
            ss << "Assert Failed \n    At File: " << __FILE__ << " \n   At Line: " << __LINE__ << "\n   ";    \
            NEPTUNE_CORE_ERROR(ss.str())                                                                      \
        }                                                                                                     \
    }                                                                                                         \

    /**
    * @brief MemoryPool's name.
    */
    static const char* memoryPoolNames[3] = {
        "System Memory Allocator",
        "Main MemoryPool Page Allocator",
        "Main MemoryPool Detail Allocator",
    };

    /**
    * @brief SharedPointer.
    *
    * @tparam T Type.
    */
    template<typename T>
    using SP = std::shared_ptr<T>;

    /**
    * @brief Create shared pointer.
    *
    * @tparam T Type.
    * 
    * @param[in] args Arguments.
    */
    template<typename T, typename ...Args>
    SP<T> CreateSP(Args&&... args)
    {
        return std::move(std::make_shared<T>(std::forward<Args>(args)...));
    }

    /**
    * @brief WeakPointer.
    *
    * @tparam T Type.
    */
    template<typename T>
    using WP = std::weak_ptr<T>;

    /**
    * @brief UniquePointer.
    *
    * @tparam T Type.
    */
    template<typename T>
    using UP = std::unique_ptr<T>;

    /**
    * @brief Create unique pointer.
    *
    * @tparam T Type.
    * 
    * @param[in] args Arguments.
    */
    template<typename T, typename ...Args>
    UP<T> CreateUP(Args&&... args)
    {
        return std::move(std::make_unique<T>(std::forward<Args>(args)...));
    }
}