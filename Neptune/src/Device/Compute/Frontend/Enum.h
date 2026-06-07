/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Compute Backend.
    */
    enum class ComputeBackendEnum : uint8_t
    {
        OpenCL = 0,            // @brief Limited Cross Platform
        SYCL,                  // @brief Limited Cross Platform
        CUDA,                  // @brief Nvidia GPU Desktop
        ROCm,                  // @brief AMD GPU Desktop

        Count
    };

}