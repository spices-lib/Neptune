/**
* @file RenderPassEncoder.h.
* @brief The RenderPassEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::RenderPassEncoder Class.
	* This class defines the WebGPU::Unit::RenderPassEncoder behaves.
	*/
	class RenderPassEncoder : public Unit<WGPURenderPassEncoder>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RenderPassEncoder() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~RenderPassEncoder() override;

		/**
		* @brief Begin RenderPassEncoder.
		* 
		* @param[in] encoder WGPUCommandEncoder.
		* @param[in] desc WGPURenderPassDescriptor.
		*/
		void Begin(WGPUCommandEncoder encoder,  const WGPURenderPassDescriptor& desc);
		
		/**
		* @brief End RenderPassEncoder.
		*/
		void End() const;

	};
}

#endif