/**
* @file Core.h.
* @brief Neptune Core Macro.
* @author Spices.
*/

#pragma once

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
            NEPTUNE_CORE_ERROR(ss.str())                                                                       \
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
}