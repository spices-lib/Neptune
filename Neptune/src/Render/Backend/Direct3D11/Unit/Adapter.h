/**
* @file Adapter.h.
* @brief The Adapter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::Adapter Class.
	* This class defines the Direct3D11::Unit::Adapter behaves.
	*/
	class Adapter : public Unit<DXGIAdapter>
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
		* @param[in] factory DXGIFactory.
		*/
		void CreateAdapter(DXGIFactory factory);

	};
}

#endif