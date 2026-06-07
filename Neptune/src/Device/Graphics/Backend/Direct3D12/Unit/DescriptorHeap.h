/**
* @file DescriptorHeap.h.
* @brief The DescriptorHeap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::DescriptorHeap Class.
	* This class defines the Direct3D12::Unit::DescriptorHeap behaves.
	*/
	class DescriptorHeap : public Unit<D3D12DescriptorHeap>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		DescriptorHeap() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorHeap() override;

		/**
		* @brief Create DescriptorHeap.
		* 
		* @param[in] device D3D12Device.
		* @param[in] desc D3D12_DESCRIPTOR_HEAP_DESC.
		*/
		void CreateDescriptorHeap(D3D12Device device, const D3D12_DESCRIPTOR_HEAP_DESC& desc);

	};
}

#endif