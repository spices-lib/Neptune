/**
* @file SYCLTest.h.
* @brief The SYCLTest Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_COMPUTE_SYCL

#include "Instrumentor.h"

#include <Device/Compute/Backend/SYCL/Sample.h>

#include <gmock/gmock.h>

namespace Neptune::SYCL::Test {

    /**
    * @brief Testing SYCL.
    */
    TEST(SYCLTest, Definition) {

        NEPTUNE_TEST_PROFILE_FUNCTION
		
    	//Sample();
    }
	
}

#endif