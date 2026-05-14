/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Device Class.
	* This class defines the WebGPU::Unit::Device behaves.
	*/
	class Device : public Unit<WGPUDevice>
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
		* 
		* @param[in] instance WGPUInstance.
		*/
		void CreateDevice(WGPUInstance instance);

	};
}

#endif