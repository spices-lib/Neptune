/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#if defined(NP_PLATFORM_WINDOWS) && defined(NP_COMPILER_CLANG)
#define NP_COMPUTE_SYCL
#endif

#ifdef NP_COMPUTE_SYCL

#include "Core/Core.h"

namespace Neptune::SYCL {

	
	
}

#endif