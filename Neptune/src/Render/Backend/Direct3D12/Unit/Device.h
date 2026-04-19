/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::Device Class.
	* This class defines the Direct3D12::Unit::Device behaves.
	*/
	class Device : public Unit<D3D12Device>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Device() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Device() override;

		/**
		* @brief Create Device.
		*/
		void CreateDevice();

	};
}

#endif