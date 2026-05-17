/**
* @file CommandEncoder.h.
* @brief The CommandEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::CommandEncoder Class.
	* This class defines the WebGPU::Unit::CommandEncoder behaves.
	*/
	class CommandEncoder : public Unit<WGPUCommandEncoder>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandEncoder() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandEncoder() override;

		/**
		* @brief Create CommandEncoder.
		* 
		* @param[in] device WGPUDevice.
		* @param[in] desc WGPUCommandEncoderDescriptor.
		*/
		void CreateCommandEncoder(WGPUDevice device,  const WGPUCommandEncoderDescriptor& desc);
	};
}

#endif