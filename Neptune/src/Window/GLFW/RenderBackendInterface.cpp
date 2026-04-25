/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderBackendInterface.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Neptune::GLFW {

	SP<APIInterface> CreateInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
			case RenderBackendEnum::OpenGL:     return CreateSP<OpenGLInterface>();
			case RenderBackendEnum::Vulkan:     return CreateSP<VulkanInterface>();
			case RenderBackendEnum::Direct3D12: return CreateSP<Direct3D12Interface>();
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in GLFW Configuration.")
				return nullptr;
			}
		}
	}

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

		// Turn off v-sync.
		glfwSwapInterval(0);

		// Use glad to load OpenGL APIs.
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			NEPTUNE_CORE_CRITICAL("Failed to initialize GLAD")
		}
	}

	void OpenGLInterface::SwapBuffers(GLFWwindow* handle) const
	{
		NEPTUNE_PROFILE_ZONE

		glfwSwapBuffers(handle);
	}

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

	void Direct3D12Interface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		// Set no OpenGL (use Direct3D12)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

}

#endif