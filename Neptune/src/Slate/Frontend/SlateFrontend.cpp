/**
* @file SlateFrontend.cpp.
* @brief The SlateFrontend Class Implementation.
* @author Spices.
*/

#include "SlateFrontend.h"
#include "Slate/Backend/ImGui/SlateBackend.h"

namespace Neptune {

	SP<SlateFrontend> SlateFrontend::Create()
	{
        NEPTUNE_PROFILE_ZONE

        SP<SlateFrontend> sp = CreateSP<ImGui::SlateBackend>();

        sp->OnInitialize();

        return sp;
	}

}