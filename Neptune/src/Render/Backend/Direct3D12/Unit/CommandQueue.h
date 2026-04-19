/**
* @file CommandQueue.h.
* @brief The CommandQueue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::CommandQueue Class.
	* This class defines the Direct3D12::Unit::CommandQueue behaves.
	*/
	class CommandQueue : public Unit<D3D12CommandQueue>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandQueue() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandQueue() override;

		/**
		* @brief Create CommandQueue.
		* 
		* @param[in] device D3D12Device.
		* @param[in] desc D3D12_COMMAND_QUEUE_DESC.
		*/
		void CreateCommandQueue(D3D12Device device, const D3D12_COMMAND_QUEUE_DESC& desc);

	};
}

#endif