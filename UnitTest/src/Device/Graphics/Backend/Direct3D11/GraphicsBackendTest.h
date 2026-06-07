/**
* @file GraphicsBackendTest.h.
* @brief The GraphicsBackendTest Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Instrumentor.h"

#include <Device/Graphics/Backend/Direct3D11/GraphicsBackend.h>

#include <gmock/gmock.h>

namespace Neptune::Direct3D11::Test {

	/**
	* @brief Testing Direct3D11::GraphicsBackend Class.
	*/
	TEST(GraphicsBackendTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		GraphicsBackend graphicsBackend;
		
		graphicsBackend.OnInitialize();
		
		graphicsBackend.OnShutDown();
	}
	
}

#endif