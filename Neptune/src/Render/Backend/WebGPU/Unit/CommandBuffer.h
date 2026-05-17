/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::CommandBuffer Class.
	* This class defines the WebGPU::Unit::CommandBuffer behaves.
	*/
	class CommandBuffer : public Unit<WGPUCommandBuffer>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandBuffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandBuffer() override;

		/**
		* @brief Create CommandBuffer.
		*
		* @param[in] encoder WGPUCommandEncoder.
		* @param[in] desc WGPUCommandBufferDescriptor.
		*/
		void CreateCommandBuffer(WGPUCommandEncoder encoder, const WGPUCommandBufferDescriptor& desc);
	};
}

#endif