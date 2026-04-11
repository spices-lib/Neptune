/**
* @file Timer.h.
* @brief The Timer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include <chrono>

namespace Neptune {
	
	/**
	* @brief Timer Class.
	*/
	class Timer
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Timer();
		
		/**
		* @brief Destructor Function.
		*/
		virtual ~Timer() = default;

		/**
		* @brief Get SegmentTime.
		* 
		* @return Returns SegmentTime.
		*/
		const float& SegmentTime() const { return m_SegmentTime; }

		/**
		* @brief Get DurationTime.
		* 
		* @return Returns DurationTime.
		*/
		const float& DurationTime() const { return m_DurationTime; }

		/**
		* @brief Flush time.
		*/
		void Flush();

	private:

		std::chrono::steady_clock::time_point m_StartTime;  // @brief Start Time.

		std::chrono::steady_clock::time_point m_LastTime;   // @brief Last Time.

		float m_SegmentTime = 0.0f;     // @brief Segment Time.

		float m_DurationTime = 0.0f;    // @brief Duration Time.
	};
}