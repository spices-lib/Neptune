#pragma once
#include "Core/Core.h"

namespace Neptune::Data {

	struct Clock
	{
		uint32_t m_FrameIndex = 0;
		uint32_t m_ImageIndex = 0;
		float    m_FrameTime = 0.0f;
		float    m_EngineTime = 0.0f;
	};
}