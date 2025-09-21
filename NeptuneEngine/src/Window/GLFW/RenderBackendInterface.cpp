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
			case RenderBackendEnum::OpenGL: return CreateSP<OpenGLInterface>();
			case RenderBackendEnum::Vulkan: return CreateSP<VulkanInterface>();
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in GLFW Configuration.")
				return nullptr;
			}
		}
	}

	void OpenGLInterface::Hint()
	{
		NEPTUNE_PROFILE_ZONE

		// Set OpenGL Version 4.6.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void OpenGLInterface::APILoad(GLFWwindow* handle)
	{
		NEPTUNE_PROFILE_ZONE

		glfwMakeContextCurrent(handle);

		// Turn off v-sync.
		glfwSwapInterval(0);

		// Use glad to load OpenGL APIs.
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			NEPTUNE_CORE_CRITICAL("Failed to initialize GLAD");
		}
	}

	void OpenGLInterface::SwapBuffers(GLFWwindow* handle)
	{
		NEPTUNE_PROFILE_ZONE

		glfwSwapBuffers(handle);
	}

	void VulkanInterface::Hint()
	{
		NEPTUNE_PROFILE_ZONE

		// Set no OpenGL (use vulkan)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

}

#endif