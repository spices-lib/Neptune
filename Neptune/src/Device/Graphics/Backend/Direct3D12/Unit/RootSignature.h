/**
* @file RootSignature.h.
* @brief The RootSignature Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::RootSignature Class.
	* This class defines the Direct3D12::Unit::RootSignature behaves.
	*/
	class RootSignature : public Unit<D3D12RootSignature>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RootSignature() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~RootSignature() override;

		/**
		* @brief Create RootSignature.
		*
		* @param[in] device D3D12Device.
		* @param[in] blob D3DBlob.
		*/
		void CreateRootSignature(D3D12Device device, D3DBlob blob);

	};
}

#endif