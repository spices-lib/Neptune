/**
* @file ImguiUtils.cpp.
* @brief The ImguiUtils Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ImguiUtils.h"

namespace Neptune {

    void ImguiSlate::Begin(float alpha, ImGuiWindowFlags flags)
    {
        Begin(m_PanelName, alpha, flags);
    }

    void ImguiSlate::Begin(const std::string& panelName, float alpha, ImGuiWindowFlags flags)
    {
        NEPTUNE_PROFILE_ZONE;

        m_WindowFlags |= flags;
        m_WindowFlags |= ImGuiWindowFlags_NoCollapse;

        // The panel
        if (alpha < 1)
        {
            ImGui::SetNextWindowBgAlpha(alpha);  // For when the panel becomes a floating window
        }

        ImGui::Begin(panelName.c_str(), &m_IsSlateOn, m_WindowFlags);

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Close"))
                m_IsSlateOn = false;
            ImGui::EndPopup();
        }

        /**
        * @brief Query Resize Event Condition.
        */
        QueryIsResizedThisFrame(ImGui::GetContentRegionAvail());

        /**
        * @brief Query Slate State, maybe implementate in parent.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Query Slate State");

            m_PanelPos   = ImGui::GetWindowPos();
            m_IsFocused  = ImGui::IsWindowFocused();
            m_IsHovered  = ImGui::IsWindowHovered();
        }
    }

    void ImguiSlate::End()
    {
        NEPTUNE_PROFILE_ZONE;

        ImGui::End(); 
    }

    void ImguiSlate::LoadSlateIcon(ImTextureID& id, const std::string& iconFile)
    {
        NEPTUNE_PROFILE_ZONE;

    }

    void ImguiSlate::QueryIsResizedThisFrame(const ImVec2& thisFrameSize)
    {
        NEPTUNE_PROFILE_ZONE;

        if (m_PanelSize.x != thisFrameSize.x || m_PanelSize.y != thisFrameSize.y)
        {
            m_IsResized = true;
        }
        else
        {
            m_IsResized = false;
        }

        m_PanelSize = thisFrameSize;
    }
}