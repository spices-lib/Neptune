/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WindowBackendInterface.h"
#include "Window/Window.h"

#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>

namespace Neptune::imgui {

	SP<WindowAPIInterface> CreateWindowInterface(WindowImplement implement)
	{
		NEPTUNE_PROFILE_ZONE

		switch (implement)
		{
			case WindowImplement::GLFW: return CreateSP<GLFWInterface>();
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported WindowImplement in ImGui Slate Configuration.")
				return nullptr;
			}
		}
	}

	void GLFWInterface::OnInitialize() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
	}

	void GLFWInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplGlfw_Shutdown();
	}

	void GLFWInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplGlfw_NewFrame();
	}

}