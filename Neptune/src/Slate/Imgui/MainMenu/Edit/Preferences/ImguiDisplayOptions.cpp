/**
* @file ImguiDisplayOptions.cpp.
* @brief The ImguiDisplayOptions Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ImguiDisplayOptions.h"
#include "World/World/World.h"

namespace Neptune {

    ImguiDisplayOptions::ImguiDisplayOptions(
        const std::string& panelName ,
        FrameInfo&         frameInfo
    )
        : ImguiSlate(panelName, frameInfo)
    {
        NEPTUNE_PROFILE_ZONE;
    }

    void ImguiDisplayOptions::OnRender()
    {
        NEPTUNE_PROFILE_ZONE;
        
        {
            NEPTUNE_PROFILE_ZONEN("ImguiDisplayOptions::Grid");

            const auto material = ResourcePool<Material>::Load<Material>("ViewportGridRenderer.ViewportGrid.Default");
            const float columeWidth = ImGuiH::GetLineItemSize().x * 10.0f;

            ImGuiH::DrawMaterial("Grid", columeWidth, material);
        }
    }
}