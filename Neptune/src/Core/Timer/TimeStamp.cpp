/**
* @file TimeStamp.cpp.
* @brief The TimeStamp Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "TimeStamp.h"

#include <time.h>

namespace Neptune {

	TimeStamp::TimeStamp()
		: m_MicroSecondsSinceEpoch(0)
	{}

	TimeStamp::TimeStamp(int64_t microSecondsSinceEpoch)
		: m_MicroSecondsSinceEpoch(microSecondsSinceEpoch)
	{}

	TimeStamp TimeStamp::Now()
	{
		return TimeStamp(time(NULL));
	}

	std::string TimeStamp::ToString() const
	{
		NEPTUNE_PROFILE_ZONE;

		char buf[128] = { 0 };
		tm* ti_time = nullptr;


		return buf;
	}
}
