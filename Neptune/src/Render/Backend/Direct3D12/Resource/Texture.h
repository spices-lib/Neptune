/**
* @file Texture.h.
* @brief The Texture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Infrastructure/Infrastructure.h"

namespace Neptune::Direct3D12 {

	/**
	* @brief Direct3D12::Texture Class.
	* This class defines the Direct3D12::Texture behaves.
	*/
	class Texture : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Texture(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Texture() override = default;

	private:

	};
}

#endif