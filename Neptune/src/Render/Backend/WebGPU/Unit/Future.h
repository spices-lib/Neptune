/**
* @file Future.h.
* @brief The Future Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Future Class.
	* This class defines the WebGPU::Unit::Future behaves.
	*/
	class Future : public Unit<WGPUFuture>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Future() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Future() override = default;

		/**
		* @brief Wait Future idle.
		*
		* @param[in] instance WGPUInstance.
		*/
		void Wait(WGPUInstance instance) const;
	};
}

#endif