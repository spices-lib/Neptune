/**
* @file Adapter.h.
* @brief The Adapter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Adapter Class.
	* This class defines the WebGPU::Unit::Adapter behaves.
	*/
	class Adapter : public Unit<WGPUAdapter>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Adapter() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Adapter() override;

		/**
		* @brief Create Adapter.
		* 
		* @param[in] instance WGPUInstance.
		*/
		void CreateAdapter(WGPUInstance instance);

	};
}

#endif