/**
* @file Debug.h.
* @brief The Debug Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::Debug Class.
	* This class defines the Direct3D12::Unit::Debug behaves.
	*/
	class Debug : public Unit<D3D12Debug>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Debug() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Debug() override;

		/**
		* @brief Create Debug.
		*/
		void CreateDebug();

		/**
		* @brief Enable Debug Layer.
		*/
		void EnableDebugLayer() const;

	};
}

#endif