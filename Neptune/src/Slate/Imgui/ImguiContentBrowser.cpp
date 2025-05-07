/**
* @file ImguiContentBrowser.cpp.
* @brief The ImguiContentBrowser Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ImguiContentBrowser.h"

namespace Neptune {

    void ImguiContentBrowser::OnRender()
    {
        NEPTUNE_PROFILE_ZONE;

        /**
        * @brief Begin render ContentBrowser.
        */
        Begin();

        /**
        * @todo Remove it.
        */
        //ImGui::ShowDemoWindow();
        //ImGui::ShowDebugLogWindow();
        //ImPlot::ShowDemoWindow();

        /**
        * @brief End render ContentBrowser.
        */
        End();
    }
}