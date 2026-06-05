/**
* @file GraphicsBackendTest.h.
* @brief The GraphicsBackendTest Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Instrumentor.h"

#include <GPURuntime/Graphics/Backend/Vulkan/GraphicsBackend.h>

#include <gmock/gmock.h>

namespace Neptune::Vulkan::Test {

	/**
	* @brief Testing Vulkan::GraphicsBackend Class.
	*/
	TEST(GraphicsBackendTest, Definition) {

		NEPTUNE_TEST_PROFILE_FUNCTION
		
		GraphicsBackend graphicsBackend;
		
		graphicsBackend.OnInitialize();
		
		graphicsBackend.OnShutDown();
	}
	
}

#endif