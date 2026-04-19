/**
* @file Resource.h.
* @brief The Resource Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::Resource Class.
	* This class defines the Direct3D12::Unit::Resource behaves.
	*/
	class Resource : public Unit<D3D12Resource>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Resource() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Resource() override;

		/**
		* @brief Create Committed Resource.
		*
		* @param[in] device D3D12Device.
		* @param[in] desc D3D12_RESOURCE_DESC.
		* @param[in] state D3D12_RESOURCE_STATES.
		* @param[in] clearValue D3D12_CLEAR_VALUE.
		*/
		void CreateCommittedResource(D3D12Device device, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, const D3D12_CLEAR_VALUE& clearValue);

		/**
		* @brief Create Placed Resource.
		*
		* @param[in] device D3D12Device.
		* @param[in] heap D3D12Heap.
		* @param[in] offset UINT64.
		* @param[in] desc D3D12_RESOURCE_DESC.
		* @param[in] state D3D12_RESOURCE_STATES.
		* @param[in] clearValue D3D12_CLEAR_VALUE.
		*/
		void CreatePlacedResource(D3D12Device device, D3D12Heap heap, UINT64 offset, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, const D3D12_CLEAR_VALUE& clearValue);

	};
}

#endif