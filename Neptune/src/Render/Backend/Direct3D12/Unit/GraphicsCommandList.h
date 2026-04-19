/**
* @file GraphicsCommandList.h.
* @brief The GraphicsCommandList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::GraphicsCommandList Class.
	* This class defines the Direct3D12::Unit::GraphicsCommandList behaves.
	*/
	class GraphicsCommandList : public Unit<D3D12GraphicsCommandList>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		GraphicsCommandList() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~GraphicsCommandList() override;

		/**
		* @brief Create GraphicsCommandList.
		*
		* @param[in] device D3D12Device.
		* @param[in] allocator D3D12CommandAllocator.
		* @param[in] type D3D12_COMMAND_LIST_TYPE.
		*/
		void CreateGraphicsCommandList(D3D12Device device, D3D12CommandAllocator allocator, D3D12_COMMAND_LIST_TYPE type);

	};
}

#endif