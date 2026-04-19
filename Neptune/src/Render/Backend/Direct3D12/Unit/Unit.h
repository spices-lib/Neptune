/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Core.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit Class.
	* This class defines the Direct3D12::Unit behaves.
	*/
	template<typename H>
	class Unit
	{
	public:

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

		Handle m_Handle{};   // @brief Unit Handle.
	};
}