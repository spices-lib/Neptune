/**
* @file ThreadQueue.hpp.
* @brief The ThreadQueue Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include <mutex>
#include <condition_variable>
#include <queue>

namespace Neptune::Container {

	template<typename T>
	class ThreadQueue
	{
	public:

		ThreadQueue() = default;

		virtual ~ThreadQueue() = default;

		template<typename T1>
		void Push(T1&& item);

		T Pop();

		bool IsEmpty() const { return m_Count.load() == 0; }

		void Clear();

	private:

		std::mutex m_Mutex;

		std::condition_variable m_NotEmpty;

		std::atomic_int m_Count = 0;

		std::queue<T> m_Queue;
	};

	template<typename T>
	template<typename T1>
	void ThreadQueue<T>::Push(T1&& item)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		m_Queue.push(item);
		++m_Count;

		m_NotEmpty.notify_all();
	}

	template<typename T>
	inline T ThreadQueue<T>::Pop()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		if (IsEmpty())
		{
			m_NotEmpty.wait(lock, [&]() { return !IsEmpty(); });
		}

		auto ptr = m_Queue.front();
		m_Queue.pop();
		--m_Count;

		return std::move(ptr);
	}

	template<typename T>
	inline void ThreadQueue<T>::Clear()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		std::queue<T>().swap(m_Queue);
		m_Count = 0;
	}
}