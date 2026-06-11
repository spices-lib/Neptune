/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D11/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/IndexBuffer.h"

namespace Neptune::Direct3D11 {

	/**
	* @brief Direct3D11::IndexBuffer Class.
	* This class defines the Direct3D11::IndexBuffer behaves.
	*/
	class IndexBuffer : public ContextAccessor, public RHI::RHIIndexBuffer::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit IndexBuffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~IndexBuffer() override = default;

	private:

	};
}

#endif