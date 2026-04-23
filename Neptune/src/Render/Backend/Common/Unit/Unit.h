/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Common/Concept.h"

namespace Neptune::Render::Common {

	/**
	* @brief Common::Unit Class.
	* This class defines the Common::Unit behaves.
	*/
	template<typename H, auto E>
	requires (IsUnitHandle<H> && IsUnitEUnit<decltype(E)>)
	class Unit
	{
	public:

		static constexpr auto E_ = E;

		using Handle = H;

	public:

		/**
		* @brief Constructor Function.
		*/
		Unit() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Unit() { ResetHandle(); }

		/**
		* @brief Get Enum of Unit.
		* 
		* @return Returns Enum of Unit.
		*/
		static const auto& GetEUnit() { return E_; }

		/**
		* @brief Set Unit Handle.
		*
		* @param[in] handle Unit Handle.
		*/
		void SetHandle(const Handle& handle) { m_Handle = handle; }

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Handle& GetHandle() const { return m_Handle; }

		/**
		* @brief Reset Unit Handle.
		*/
		void ResetHandle() { m_Handle = {}; }

	protected:

		Handle m_Handle{};      // @brief Unit Handle.
	};
}