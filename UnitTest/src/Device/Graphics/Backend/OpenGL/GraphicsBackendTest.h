/**
* @file GraphicsBackendTest.h.
* @brief The GraphicsBackendTest Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Instrumentor.h"

#include <Device/Graphics/Backend/OpenGL/GraphicsBackend.h>

#include <gmock/gmock.h>

namespace Neptune::OpenGL::Test {

    /**
    * @brief Testing OpenGL::GraphicsBackend Class.
    */
    TEST(GraphicsBackendTest, Definition) {

        NEPTUNE_TEST_PROFILE_FUNCTION
		
        GraphicsBackend graphicsBackend;
		
        graphicsBackend.OnInitialize();
		
        graphicsBackend.OnShutDown();
    }
	
}

#endif