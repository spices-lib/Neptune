/**
* @file DebugDevice.h.
* @brief The DebugDevice Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::DebugDevice Class.
	* This class defines the Direct3D12::Unit::DebugDevice behaves.
	*/
	class DebugDevice : public Unit<D3D12DebugDevice>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		DebugDevice() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~DebugDevice() override;

		/**
		* @brief Create DebugDevice.
		* 
		* @param[in] device D3D12Device.
		*/
		void CreateDebugDevice(D3D12Device device);

	};
}

#endif