/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackendInterface.h"

#include <GLFW/glfw3.h>

namespace Neptune::GLFW {

	SP<APIInterface> CreateInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
#ifdef NP_GRAPHICS_OPENGL
			case RenderBackendEnum::OpenGL:     return CreateSP<OpenGLInterface>();
#endif
			
#ifdef NP_GRAPHICS_VULKAN
			case RenderBackendEnum::Vulkan:     return CreateSP<VulkanInterface>();
#endif
			
#ifdef NP_GRAPHICS_DIRECT3D11
			case RenderBackendEnum::Direct3D11: return CreateSP<Direct3D11Interface>();
#endif
			
#ifdef NP_GRAPHICS_DIRECT3D12
			case RenderBackendEnum::Direct3D12: return CreateSP<Direct3D12Interface>();
#endif
			
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in GLFW Configuration.")
				return nullptr;
			}
		}
	}

#ifdef NP_GRAPHICS_OPENGL
	
	void OpenGLInterface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		// Set OpenGL Version 4.6.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef NEPTUNE_DEBUG

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#endif

	}

	void OpenGLInterface::APILoad(GLFWwindow* handle) const
	{
		NEPTUNE_PROFILE_ZONE

		glfwMakeContextCurrent(handle);
	}

#endif
	
#ifdef NP_GRAPHICS_VULKAN
	
	void VulkanInterface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		// Set no OpenGL (use Vulkan)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}
	
	std::vector<const char*> VulkanInterface::Extension() const
	{
		NEPTUNE_PROFILE_ZONE
		
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		
		return std::vector(glfwExtensions, glfwExtensions + glfwExtensionCount);
	}
	
#endif
	
#ifdef NP_GRAPHICS_DIRECT3D11

	void Direct3D11Interface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		// Set no OpenGL (use Direct3D11)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}
	
#endif
	
#ifdef NP_GRAPHICS_DIRECT3D12
	
	void Direct3D12Interface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		// Set no OpenGL (use Direct3D12)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

#endif
	
}

#endif