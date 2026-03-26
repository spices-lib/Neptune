#pragma once
#include "Core/Core.h"
#include <chrono>

namespace Neptune {

	class Timer
	{
	public:

		Timer();
		virtual ~Timer() = default;

		const float& SegmentTime() const { return m_SegmentTime; }

		const float& DurationTime() const { return m_DurationTime; }

		void Flush();

	public:

		std::chrono::steady_clock::time_point m_StartTime;

		std::chrono::steady_clock::time_point m_LastTime;

		float m_SegmentTime = 0.0f;

		float m_DurationTime = 0.0f;
	};
}