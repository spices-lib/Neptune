/**
* @file ImguiMainMenu.cpp.
* @brief The ImguiGizmos Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ImguiMainMenu.h"
#include "Core/Input/Input.h"
#include "Systems/SlateSystem.h"
#include "..\..\..\Core\Thread\ThreadModel.h"
#include "Slate/SlateStyleLayout.h"
#include <imgui_internal.h>

namespace Neptune {

    ImguiMainMenu::ImguiMainMenu(
        const std::string& panelName , 
        FrameInfo&         frameInfo
    )
        : ImguiSlate(panelName, frameInfo)
    {
        NEPTUNE_PROFILE_ZONE;

        /**
        * @brief Instance Child Item.
        */
        {

        }
    }

    void ImguiMainMenu::OnRender()
	{
        NEPTUNE_PROFILE_ZONE;

	}

    void ImguiMainMenu::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
    }
}