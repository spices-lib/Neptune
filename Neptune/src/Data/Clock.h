/**
* @file Clock.h.
* @brief The Clock Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Data {

	/**
	* @brief Engine Clock.
	*/
	struct Clock
	{
		uint32_t m_FrameIndex = 0;         // @brief Render Frame Index.
		uint32_t m_ImageIndex = 0;         // @brief Swapchain image Index.
		float    m_FrameTime = 0.0f;       // @brief Frame Run Time.
		float    m_EngineTime = 0.0f;      // @brief Engine Run Time.
	};
}