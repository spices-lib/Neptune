/**
* @file DelegateBasic.h
* @brief The Delegate_Basic Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/LinkedUnorderedMap.h"

#include <functional>

namespace Neptune {

	/**
	* @brief Basic Class of Delegate.
	* Instance inherited from it and use delegate feature.
	*/
	template<typename... Args>
	class Delegate_Basic
	{
	public:

		/**
		* @brief Agent Function.
		*/
		using Agent = std::function<void(Args...)>;

	public:

		/**
		* @brief Constructor Function.
		*/
		Delegate_Basic()
		{
			m_Agents = CreateSP<Container::LinkedUnorderedMap<uint64_t, Agent>>();
		}

		/**
		* @brief Destructor Function.
		*/
		virtual ~Delegate_Basic() = default;

		/**
		* @brief Bind Function pointer to delegate.
		* 
		* @param[in] func Function pointer.
		* 
		* @return Returns true if bind successfully.
		*/
		bool Bind(std::function<void(Args...)> func);

		/**
		* @brief UnBind Function pointer from delegate.
		* 
		* @param[in] func Function pointer.
		* 
		* @return Returns true if unbind successfully.
		*/
		bool UnBind(std::function<void(Args...)> func);

		/**
		* @brief Get size of Agents.
		* 
		* @return Returns the size of Agents.
		*/
		size_t Size() const { return m_Agents->size(); }

		/**
		* @brief Determine if this Delegate is empty;
		* 
		* @return Returns true if empty.
		*/
		bool empty() const { return m_Agents->size() == 0; }

		/**
		* @brief Execute all function pointer. 
		*/
		void Broadcast(Args&&... args);

	private:
		
		SP<Container::LinkedUnorderedMap<uint64_t, Agent>> m_Agents;  // @brief Map of Agent Function Pointer.
	};

	template<typename ...Args>
	inline bool Delegate_Basic<Args...>::Bind(std::function<void(Args...)> func)
	{
		NEPTUNE_PROFILE_ZONE

		uint64_t* addr = reinterpret_cast<uint64_t*>(&func);
		
		if (m_Agents->Contains(*addr))
		{
			NEPTUNE_CORE_WARN("Agent Function binding repeatedly.")
			
			return false;
		}
		
		m_Agents->PushBack(*addr, func);

		return true;
	}

	template<typename ...Args>
	inline bool Delegate_Basic<Args...>::UnBind(std::function<void(Args...)> func)
	{
		NEPTUNE_PROFILE_ZONE

		uint64_t* addr = reinterpret_cast<uint64_t*>(&func);
		if (!m_Agents->has_key(*addr))
		{
			NEPTUNE_CORE_WARN("Agent Function not bound yet.")
			
			return false;
		}
		
		m_Agents->Erase(*addr);

		return true;
	}

	template<typename ...Args>
	inline void Delegate_Basic<Args...>::Broadcast(Args&&... args)
	{
		NEPTUNE_PROFILE_ZONE

		m_Agents->ForEach([&](const auto& k, const auto& v) {
			
			std::invoke(v, std::forward<Args>(args)...);
			
			return false;
		});
	}

/**
* @brief Use this macro to instance a Delegate Class.
* Any Parameter Specific.
*/
#define DELEGATE(name, ...)                                                \
	class Delegate##name : public Neptune::Delegate_Basic<__VA_ARGS__>     \
	{                                                                      \
	public:                                                                \
		Delegate##name() : Neptune::Delegate_Basic<__VA_ARGS__>() {}       \
		virtual ~Delegate##name() = default;                               \
	}; 

}