/**
* @file GraphicsBackendTest.h.
* @brief The GraphicsBackendTest Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Instrumentor.h"

#include <GPURuntime/Graphics/Backend/Metal/GraphicsBackend.h>

#include <gmock/gmock.h>

namespace Neptune::Metal::Test {

	/**
	* @brief Testing Metal::GraphicsBackend Class.
	*/
	TEST(GraphicsBackendTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		GraphicsBackend graphicsBackend;
		
		graphicsBackend.OnInitialize();
		
		graphicsBackend.OnShutDown();
	}
	
}

#endif