/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Queue Class.
	* This class defines the WebGPU::Unit::Queue behaves.
	*/
	class Queue : public Unit<WGPUQueue>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Queue() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Queue() override;

		/**
		* @brief Create Queue.
		*
		* @param[in] device WGPUDevice.
		*/
		void CreateQueue(WGPUDevice device);
	};
}

#endif