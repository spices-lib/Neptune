/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackendInterface.h"

#include <emscripten.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>

#include <GLFW/glfw3.h>
#include <GLFW/emscripten_glfw3.h>

namespace Neptune::EmscriptenGLFW {

	SP<APIInterface> CreateInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
			case RenderBackendEnum::WebGL:      return CreateSP<WebGLInterface>();
			case RenderBackendEnum::WebGPU:     return CreateSP<WebGPUInterface>();
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in GLFW Configuration.")
				return nullptr;
			}
		}
	}

	void WebGLInterface::APILoad(GLFWwindow* handle) const
	{
		NEPTUNE_PROFILE_ZONE

		EmscriptenWebGLContextAttributes attrs;

        emscripten_webgl_init_context_attributes(&attrs);

        auto ctx = emscripten_webgl_create_context("#nepnep", &attrs);

        emscripten_webgl_make_context_current(ctx);
	}

}

#endif