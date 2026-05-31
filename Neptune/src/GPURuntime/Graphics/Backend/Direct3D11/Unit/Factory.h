/**
* @file Factory.h.
* @brief The Factory Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::Factory Class.
	* This class defines the Direct3D11::Unit::Factory behaves.
	*/
	class Factory : public Unit<DXGIFactory>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Factory() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Factory() override;

		/**
		* @brief Create Factory.
		* 
		* @param[in] flags DXGIFlags
		*/
		void CreateFactory(UINT flags);

	};
}

#endif