/**
* @file Timer.cpp.
* @brief The Timer Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Timer.h"

namespace Neptune {

	Timer::Timer()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_StartTime = std::chrono::high_resolution_clock::now();
		m_LastTime  = std::chrono::high_resolution_clock::now();
	}

	void Timer::Flush()
	{
		NEPTUNE_PROFILE_ZONE
		
		const auto nowTime = std::chrono::high_resolution_clock::now();

		m_SegmentTime = std::chrono::duration<float, std::chrono::seconds::period>(nowTime - m_LastTime).count();

		m_DurationTime = std::chrono::duration<float, std::chrono::seconds::period>(nowTime - m_StartTime).count();

		m_LastTime = nowTime;
	}
}