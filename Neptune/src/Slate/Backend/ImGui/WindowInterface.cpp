/**
* @file WindowInterface.cpp.
* @brief The WindowInterface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "WindowInterface.h"
#include "Window/Window.h"

#include <backends/imgui_impl_glfw.h>

namespace Neptune::imgui {

	SP<WindowInterface> CreateWindowInterface(WindowImplement implement)
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

	void GLFWInterface::OnInitialize(RenderBackendEnum e) const
	{
		NEPTUNE_PROFILE_ZONE

		switch (e)
		{
			case RenderBackendEnum::OpenGL:
			{
				ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			case RenderBackendEnum::Vulkan:
			{
				ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(Window::Instance().NativeWindow()), true);
				break;
			}
			default:
			{
				NEPTUNE_CORE_ERROR("Unsupported RenderBackendEnum in GLFWInterface::OnInitialize.")
				break;
			}
		}
		
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