/**
* @file UserDefinedAnnotation.h.
* @brief The UserDefinedAnnotation Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D11::Unit {

	/**
	* @brief Direct3D11::Unit::UserDefinedAnnotation Class.
	* This class defines the Direct3D11::Unit::UserDefinedAnnotation behaves.
	*/
	class UserDefinedAnnotation : public Unit<D3DUserDefinedAnnotation>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		UserDefinedAnnotation() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~UserDefinedAnnotation() override;

		/**
		* @brief Create UserDefinedAnnotation.
		*
		* @param[in] deviceContext D3D11DeviceContext.
		*/
		void CreateUserDefinedAnnotation(D3D11DeviceContext deviceContext);
		
	};
}

#endif