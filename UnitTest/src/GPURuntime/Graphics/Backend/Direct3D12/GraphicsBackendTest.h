/**
* @file GraphicsBackendTest.h.
* @brief The GraphicsBackendTest Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Instrumentor.h"

#include <GPURuntime/Graphics/Backend/Direct3D12/GraphicsBackend.h>

#include <gmock/gmock.h>

namespace Neptune::Direct3D12::Test {

	/**
	* @brief Testing Direct3D12::GraphicsBackend Class.
	*/
	TEST(GraphicsBackendTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		GraphicsBackend graphicsBackend;
		
		graphicsBackend.OnInitialize();
		
		graphicsBackend.OnShutDown();
	}
	
}

#endif