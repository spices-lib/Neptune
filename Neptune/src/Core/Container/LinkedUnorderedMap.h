/**
* @file LinkedUnorderedMap.h.
* @brief The LinkedUnorderedMap Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#include "Core/Core.h"

#include <unordered_map>
#include <shared_mutex>
#include <list>

namespace Neptune::Container {

	/**
	* @brief The container combines hashmap and list together.
	* Used in the case that we want iter a hashmap in order.
	* Thread Safe.
	*/
	template<typename K, typename V>
	class LinkedUnorderedMap
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		LinkedUnorderedMap()
			: m_Size(0)
		{};

		/**
		* @brief Destructor Function.
		*/
		virtual ~LinkedUnorderedMap() = default;

		/**
		* @brief Clear this container's data.
		*/
		void Clear();

		/**
		* @brief The container's element size.
		* 
		* @return Returns the size of the container.
		*/
		size_t Size() const;

		/**
		* @brief Add an element to this container.
		* 
		* @param[in] key K the key.
		* @param[in] value V the value.
		*/
		void PushBack(const K& key, const V& value);

		/**
		* @brief Find the value by key.
		* 
		* @param[in] key K the key.
		* 
		* @return Returns the value that founded.
		*/
		V& At(const K& key);

		/**
		* @brief Determine whether the key is in the container.
		* 
		* @param[in] key K the key.
		* 
		* @return Returns true if it has key inside the container.
		*/
		bool Contains(const K& key) const;

		/**
		* @brief Remove an element inside the container if founded by key.
		* 
		* @param[in] key K the key.
		*/
		void Erase(const K& key);

		/**
		* @brief Iter the container in order.
		* 
		* @param[in] fn The function of how to iter the container.
		*/
		template<typename F>
		void ForEach(F&& fn);
		
		/**
		* @brief Get the previous element by the key.
		* 
		* @param[in] key the key.
		* 
		* @return Returns the previous element.
		* 
		* @note It's slow, so do not use it unnecessary. 
		*/
		V& Prev(const K& key);

		/**
		* @brief Get the next element by the key.
		* 
		* @param[in] key the key.
		* 
		* @return Returns the next element.
		* 
		* @note It's slow, so do not use it unnecessary. 
		*/
		V& Next(const K& key);

		/**
		* @brief Get the first element of this container.
		* 
		* @return Returns the first element found.
		*/
		V& Begin();

		/**
		* @brief Get the end element of this container.
		* 
		* @return Returns the end element found.
		*/
		V& End();

		/**
		* @breif Get the end key of this container.
		* 
		* @return Returns the end key found.
		*/
		const K& EndK();
		
	private:
		
		std::list<K> m_Keys;                 // @brief The container keeps iter in order.
		std::unordered_map<K, V> m_Map;      // @breif The container keeps quick search.
		mutable std::shared_mutex m_Mutex;   // @brief Mutex for this container.
		std::atomic_int m_Size;              // @brief This container size.
	};

	template<typename K, typename V>
	inline void LinkedUnorderedMap<K, V>::Clear()
	{
		std::unique_lock lock(m_Mutex);

		m_Keys.clear();
		m_Map.clear();
		m_Size = 0;
	}

	template<typename K, typename V>
	inline size_t LinkedUnorderedMap<K, V>::Size() const
	{
		return m_Size.load();
	}

	template<typename K, typename V>
	inline void LinkedUnorderedMap<K, V>::PushBack(const K& key, const V& value)
	{
		auto hasKey = Contains(key);

		std::unique_lock lock(m_Mutex);

		if (!hasKey)
		{
			m_Keys.push_back(key);

			++m_Size;
		}

		m_Map[key] = value;
	}

	template<typename K, typename V>
	inline V& LinkedUnorderedMap<K, V>::At(const K& key)
	{
		auto hasKey = Contains(key);

		std::shared_lock lock(m_Mutex);

		if (hasKey)
		{
			return m_Map[key];
		}

		return {};
	}

	template<typename K, typename V>
	inline bool LinkedUnorderedMap<K, V>::Contains(const K& key) const
	{
		std::shared_lock lock(m_Mutex);

		return m_Map.contains(key);
	}

	template<typename K, typename V>
	inline void LinkedUnorderedMap<K, V>::Erase(const K& key)
	{
		std::unique_lock lock(m_Mutex);

		auto it = m_Map.find(key);
		
		if (it != m_Map.end())
		{
			m_Keys.remove(key);
			
			m_Map.erase(it);

			--m_Size;
		}
	}

	template<typename K, typename V>
	template<typename F>
	inline void LinkedUnorderedMap<K, V>::ForEach(F&& fn)
	{
		std::shared_lock lock(m_Mutex);

		for (const K& key : m_Keys)
		{
			/**
			* @brief The function defines how to iter.
			* 
			* @param[in] key K the key.
			* @param[in] value V the value.
			* 
			* @return Retunrs True if want break this for loop.
			*/
			if(std::invoke(fn, key, m_Map[key])) break;
		}
	}

	template<typename K, typename V>
	inline V& LinkedUnorderedMap<K, V>::Prev(const K& key)
	{
		if (!Contains(key)) return {};

		std::shared_lock lock(m_Mutex);
		
		if (key == m_Keys.front()) return {};
		
		for (auto it = m_Keys.begin(); it != m_Keys.end(); ++it)
		{
			if (*it == key)
			{
				return (*std::prev(it));
			}
		}

		return {};
	}

	template<typename K, typename V>
	inline V& LinkedUnorderedMap<K, V>::Next(const K& key)
	{
		if (!Contains(key)) return {};

		std::shared_lock lock(m_Mutex);
		
		if (key == m_Keys.back()) return {};
		
		for (auto it = m_Keys.begin(); it != m_Keys.end(); ++it)
		{
			if (*it == key)
			{
				return (*std::next(it));
			}
		}

		return {};
	}

	template<typename K, typename V>
	V& LinkedUnorderedMap<K, V>::Begin()
	{
		std::shared_lock lock(m_Mutex);

		if (Size() == 0) return {};

		return m_Map[m_Keys.front()];
	}

	template<typename K, typename V>
	V& LinkedUnorderedMap<K, V>::End()
	{
		std::shared_lock lock(m_Mutex);

		if (Size() == 0) return {};

		return m_Map[m_Keys.back()];
	}

	template<typename K, typename V>
	const K& LinkedUnorderedMap<K, V>::EndK()
	{
		std::shared_lock lock(m_Mutex);

		if (Size() == 0) return {};

		return m_Keys.back();
	}
}