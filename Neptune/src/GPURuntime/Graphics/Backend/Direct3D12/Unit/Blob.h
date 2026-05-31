/**
* @file Blob.h.
* @brief The Blob Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::Blob Class.
	* This class defines the Direct3D12::Unit::Blob behaves.
	*/
	class Blob : public Unit<D3DBlob>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Blob() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Blob() override;

		/**
		* @brief Create Blob.
		* 
		* @param[in] desc D3D12_VERSIONED_ROOT_SIGNATURE_DESC.
		*/
		void CreateBlob(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& desc);

	};
}

#endif