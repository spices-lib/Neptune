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
        OpenCL = 0,            // @brief Limited Desktop & Mobile
        SYCL,                  // @brief Limited Desktop
        CUDA,                  // @brief Nvidia GPU Desktop
        ROCm,                  // @brief AMD GPU Desktop
        OpenMP,                // @brief CPU Cross Platform
        HIP,                   // @brief IR (CUDA/ROCm) GPU Desktop

        Count
    };

}