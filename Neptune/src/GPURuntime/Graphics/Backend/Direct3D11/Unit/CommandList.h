/**
* @file CommandList.h.
* @brief The CommandList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::CommandList Class.
	* This class defines the Direct3D11::Unit::CommandList behaves.
	*/
	class CommandList : public Unit<D3D11CommandList>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandList() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandList() override;

	};
}

#endif