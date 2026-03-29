/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit Class.
	* This class defines the Vulkan::Unit behaves.
	*/
	template<typename H, VkObjectType E_>
	class Unit
	{
	public:

		static constexpr VkObjectType E = E_;

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
		static const VkObjectType& GetEUnit() { return E; }

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
		void ResetHandle() { m_Handle = nullptr; }

	protected:

		Handle m_Handle = nullptr;   // @brief Unit Handle.
	};
}