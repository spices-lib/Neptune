/**
* @file FrameInfo.h.
* @brief The FrameInfo Class Definitions.
* @author Spices.
*/

#include "Pchheader.h"
#include "FrameInfo.h"

namespace Neptune
{
	static FrameInfo m_FrameInfo;

	FrameInfo& FrameInfo::Get()
	{
		return m_FrameInfo;
	}
}