/**
* @file InfoQueue.h.
* @brief The InfoQueue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::InfoQueue Class.
	* This class defines the Direct3D12::Unit::InfoQueue behaves.
	*/
	class InfoQueue : public Unit<D3D12InfoQueue>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		InfoQueue() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~InfoQueue() override;

		/**
		* @brief Create InfoQueue.
		* 
		* @param[in] device D3D12Device.
		*/
		void CreateInfoQueue(D3D12Device device);

	};
}

#endif