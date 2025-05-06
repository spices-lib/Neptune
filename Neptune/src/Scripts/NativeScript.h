/**
* @file NativeScript.h.
* @brief The NativeScript & NativeScriptRegister Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace Neptune {
	
	/**
	* @brief Native C++ Script Class.
	*/
	class NativeScript
	{
	public:
		
		/**
		* @brief Constructor Function.
		*/
		NativeScript() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~NativeScript() = default;

		/**
		* @brief This interface defines the behave on specific component tick every frame.
		* @param[in] ts TimeStep.
		*/
		virtual void OnTick(TimeStep& ts) = 0;

		/**
		* @brief This interface defines the behave on specific component event happened.
		* @param[in] e Event.
		*/
		virtual void OnEvent(Event& e) = 0;
	};

	/**
	* @brief Registry Native C++ Script Class.
	*/
	class NativeScriptRegister
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		NativeScriptRegister() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~NativeScriptRegister() = default;

		/**
		* @brief Copy Constructor Function.
		* @note This Class not allowed copy behave.
		*/
		NativeScriptRegister(const NativeScriptRegister&) = delete;

		/**
		* @brief Copy Assignment Operation.
		* @note This Class not allowed copy behaver.
		*/
		NativeScriptRegister& operator=(const NativeScriptRegister&) = delete;

		/**
		* @brief This function registry slate instance.
		* @tparam T Slate specific type.
		*/
		template<typename T, typename ... Args>
		void Register(Args&& ... args);

		/**
		* @note This function is not in use now.
		* @param[in] ts TimeStep.
		*/
		void OnUpdate(TimeStep& ts) const;

		/**
		* @brief This function will be called on global Event function pointer is called.
		*/
		void OnEvent(Event& event) const;

	private:

		/**
		* @brief The container of all native script handle.
		*/
		std::vector<std::unique_ptr<NativeScript>> m_NativeScripts;
	};

	template<typename T, typename ...Args>
	inline void NativeScriptRegister::Register(Args && ...args)
	{
		m_NativeScripts.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
}