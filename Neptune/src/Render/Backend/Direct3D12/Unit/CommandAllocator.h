/**
* @file CommandAllocator.h.
* @brief The CommandAllocator Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::CommandAllocator Class.
	* This class defines the Direct3D12::Unit::CommandAllocator behaves.
	*/
	class CommandAllocator : public Unit<D3D12CommandAllocator>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandAllocator() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandAllocator() override;

		/**
		* @brief Create CommandAllocator.
		*
		* @param[in] device D3D12Device.
		* @param[in] type D3D12_COMMAND_LIST_TYPE.
		*/
		void CreateCommandAllocator(D3D12Device device, D3D12_COMMAND_LIST_TYPE type);

	};
}

#endif