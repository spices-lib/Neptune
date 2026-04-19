/**
* @file CmdList2.cpp.
* @brief The CmdList2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "CmdList2.h"
#include "Render/Backend/OpenGL/Infrastructure/Context.h"
#include "Render/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"
#include "World/Component/ClockComponent.h"

namespace Neptune::OpenGL {

	void CmdList2::Begin() const
	{
		NEPTUNE_PROFILE_ZONE

	}

	void CmdList2::End() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList2::SubmitWait()
	{
		NEPTUNE_PROFILE_ZONE

		glFlush();
	}

	void CmdList2::SetGraphicCmdList()
	{
		NEPTUNE_PROFILE_ZONE

	}

	void CmdList2::SetVideoDecodeCmdList()
	{
		NEPTUNE_PROFILE_ZONE

	}

	void CmdList2::SetOpticalFlowCmdList()
	{
		NEPTUNE_PROFILE_ZONE

	}

}

#endif