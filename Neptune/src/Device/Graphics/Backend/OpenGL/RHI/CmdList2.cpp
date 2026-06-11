/**
* @file CmdList2.cpp.
* @brief The CmdList2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "CmdList2.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/DebugUtilsObject.h"

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