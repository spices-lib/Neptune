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

	/**
	* @brief thread safe queue.
	* 
	* @tparam T specific stored type.
	*/
	template<typename T>
	class ThreadQueue
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		ThreadQueue() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~ThreadQueue() = default;

		/**
		* @brief Push item to this queue.
		* 
		* @param[in] item The item.
		*/
		template<typename T1>
		void Push(T1&& item);

		/**
		* @brief Push item from this queue.
		* 
		* @return Returns item.
		*/
		T Pop();

		/**
		* @brief If this queue empty.
		* 
		* @return Returns true if empty.
		*/
		bool IsEmpty() const { return m_Count.load() == 0; }

		/**
		* @brief Clear this queue.
		*/
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
		std::unique_lock lock(m_Mutex);

		m_Queue.push(item);
		
		++m_Count;

		m_NotEmpty.notify_all();
	}

	template<typename T>
	inline T ThreadQueue<T>::Pop()
	{
		std::unique_lock lock(m_Mutex);

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
		std::unique_lock lock(m_Mutex);

		std::queue<T>().swap(m_Queue);
		
		m_Count = 0;
	}
}