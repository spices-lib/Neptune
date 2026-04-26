/**
* @file Fence.h.
* @brief The Fence Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::Fence Class.
	* This class defines the Direct3D12::Unit::Fence behaves.
	*/
	class Fence : public Unit<D3D12Fence>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Fence() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Fence() override;

		/**
		* @brief Create Fence.
		*
		* @param[in] device D3D12Device.
		*/
		void CreateFence(D3D12Device device);

		/**
		* @brief Get Next wait value.
		*
		* @return Returns Next wait value.
		*/
		uint64_t GetNextWaitValue();
		
		/**
		* @brief Fence wait idle.
		*/
		void Wait() const;
		
	private:

		HANDLE m_Event;                 // @brief Fence Event.
		uint64_t m_Value;               // @brief Wait value.
		
	};
}

#endif