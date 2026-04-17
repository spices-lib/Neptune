/**
* @file SlateBackend.cpp.
* @brief The SlateBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SlateBackend.h"
#include "RenderInterface.h"
#include "WindowInterface.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui.cpp>
#include <imgui_internal.h>
#include <imgui_widgets.cpp>

namespace Neptune::imgui {

    SlateBackend::SlateBackend(RenderBackendEnum renderBackend, WindowImplement windowImpl)
        : SlateFrontend(SlateBackendEnum::ImGui)
        , m_RenderInterface(CreateRenderInterface(renderBackend))
        , m_WindowInterface(CreateWindowInterface(windowImpl))
        , m_RenderBackendEnum(renderBackend)
        , m_WindowImplement(windowImpl)
    {}

    void SlateBackend::OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure)
    {
        NEPTUNE_PROFILE_ZONE

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.IniFilename     = "Layout.ini";
		io.LogFilename     = nullptr;
		io.ConfigFlags    |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags    |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags    |= ImGuiConfigFlags_ViewportsEnable;

        m_WindowInterface->OnInitialize(m_RenderBackendEnum);
        m_RenderInterface->OnInitialize(infrastructure);
    }

    void SlateBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_WindowInterface->OnShutDown();
        m_RenderInterface->OnShutDown();

		ImGui::DestroyContext();
    }

    void SlateBackend::BeginFrame()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderInterface->BeginFrame();
        m_WindowInterface->BeginFrame();

		ImGui::NewFrame();

        ImGuiID dockspaceID = ImGui::GetID("DockSpace");

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags host_window_flags = 0;
        host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        host_window_flags |= ImGuiWindowFlags_NoMove; //| ImGuiWindowFlags_NoDocking;
        host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        host_window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::GetStyle().WindowPadding = ImVec2(2.0f, 2.0f);

        char label[32];
        ImFormatString(label, IM_ARRAYSIZE(label), "DockSpaceViewport_%08X", viewport->ID);
        ImGui::Begin(label, NULL, host_window_flags);

        ImGuiDockNodeFlags dockspaceFlags =
        ImGuiDockNodeFlags_PassthruCentralNode;
        //ImGuiDockNodeFlags_AutoHideTabBar;
        //ImGuiDockNodeFlags_NoDockingInCentralNode;

        if (!ImGui::DockBuilderGetNode(dockspaceID))
        {
            ImGui::DockBuilderRemoveNode(dockspaceID);
            ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);

            ImGuiID dock_main_id = dockspaceID;

            ImGuiID id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_left", id_left);

            ImGuiID id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_right", id_right);

            ImGuiID id_up = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_up", id_up);

            ImGuiID id_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
            ImGui::DockBuilderDockWindow("Dock_down", id_down);

            ImGui::DockBuilderDockWindow("Scene", dock_main_id);

            ImGui::DockBuilderFinish(dock_main_id);
        }

        ImVec4 col = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(col.x, col.y, col.z, 1.0f));
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
        ImGui::PopStyleColor();
        ImGui::End();
    }

    void SlateBackend::EndFrame()
    {}

}