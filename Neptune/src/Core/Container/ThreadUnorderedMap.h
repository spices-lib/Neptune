/**
* @file ThreadUnorderedMap.h.
* @brief The ThreadUnorderedMap Class Definitions.
* @author spices.
*/

#pragma once
#include "Core/Core.h"
#include <shared_mutex>

namespace Neptune::Container {

	/**
	* @brief Thread safe std::unordered_map.
	*/
	template<typename K, typename V>
	class ThreadUnorderedMap
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		ThreadUnorderedMap() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~ThreadUnorderedMap() = default;

		/**
		* @brief Is this queue is empty.
		* 
		* @reutrn Returns true if empty.
		*/
		bool Empty() const { return m_Count.load() == 0; }

		/**
		* @brief Insert an element to this.
		* 
		* @param[in] k Key.
		* @param[in] v Value.
		*/
		void Insert(const K& k, const V& v);

		/**
		* @brief Find element in this unordered_map.
		* 
		* @param[in] k Key.
		* 
		* @return Returns value.
		*/
		V& At(const K& k);

		/**
		* @brief Erase element in this unordered_map.
		* 
		* @param[in] k Key.
		*/
		void Erase(const K& k);
		
		/**
		* @brief Is element in this unordered_map.
		* 
		* @param[in] k Key.
		* 
		* @return Returns true if found.
		*/
		bool Contains(const K& k) const;

		/**
		* @brief Clear this unordered_map.
		*/
		void Clear();

	private:
		
		mutable std::shared_mutex m_Mutex;    // @brief Mutex of this queue.
		std::unordered_map<K, V> m_Map;       // @brief This wrapped unordered_map.
		std::atomic_uint32_t m_Count;         // @brief elements of this unordered_map.
		
	};
	
	template<typename K, typename V>
	inline void ThreadUnorderedMap<K, V>::Insert(const K& k, const V& v)
	{
		std::unique_lock lock(m_Mutex);

		if (!Contains(k))
		{
			++m_Count;
		}
		
		m_Map[k] = v;
	}
	
	template<typename K, typename V>
	inline V& ThreadUnorderedMap<K, V>::At(const K& k)
	{
		std::shared_lock lock(m_Mutex);

		return m_Map[k];
	}
	
	template<typename K, typename V>
	inline void ThreadUnorderedMap<K, V>::Erase(const K& k)
	{
		std::unique_lock lock(m_Mutex);

		if (!Contains(k)) return;
		
		m_Map.erase(k);
		
		--m_Count;
	}

	template<typename K, typename V>
	inline bool ThreadUnorderedMap<K, V>::Contains(const K& k) const
	{
		std::shared_lock lock(m_Mutex);

		return m_Map.contains(k);
	}

	template<typename K, typename V>
	inline void ThreadUnorderedMap<K, V>::Clear()
	{
		std::unique_lock lock(m_Mutex);

		m_Map.clear();
		
		m_Count = 0;
	}
}