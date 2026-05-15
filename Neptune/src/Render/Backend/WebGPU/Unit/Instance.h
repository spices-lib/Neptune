/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Instance Class.
	* This class defines the WebGPU::Unit::Instance behaves.
	*/
	class Instance : public Unit<WGPUInstance>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Instance() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Instance() override;

		/**
		* @brief Create Instance.
		*
		* @param[in] descriptor WGPUInstanceDescriptor.
		*/
		void CreateInstance(const WGPUInstanceDescriptor& descriptor);
	};
}

#endif