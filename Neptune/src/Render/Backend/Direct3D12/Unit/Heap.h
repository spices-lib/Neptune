/**
* @file Heap.h.
* @brief The Heap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::Heap Class.
	* This class defines the Direct3D12::Unit::Heap behaves.
	*/
	class Heap : public Unit<D3D12PipelineState>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Heap() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Heap() override;

		/**
		* @brief Create Heap.
		*
		* @param[in] device D3D12Device.
		* @param[in] desc D3D12_HEAP_DESC.
		*/
		void CreateHeap(D3D12Device device, const D3D12_HEAP_DESC& desc);

	};
}

#endif