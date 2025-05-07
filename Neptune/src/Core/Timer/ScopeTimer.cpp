/**
* @file ScopeTimer.cpp.
* @brief The ScopeTimer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ScopeTimer.h"

namespace Neptune {

	Neptune::ScopeTimer::ScopeTimer(const std::string& log)
		: m_Log(log)
	{
		/**
		* @brief Init In Time.
		*/
		m_InTime = std::chrono::high_resolution_clock::now();
	}

	Neptune::ScopeTimer::~ScopeTimer()
	{
		/**
		* @brief Init Leave Time.
		*/
		m_LeaveTime = std::chrono::high_resolution_clock::now();

		std::stringstream ss;
		ss << "ScopeTimer : " << std::chrono::duration<float, std::chrono::milliseconds::period>(m_LeaveTime - m_InTime).count() << " milliseconds " << m_Log;

		NEPTUNE_CORE_INFO(ss.str())
	}

}