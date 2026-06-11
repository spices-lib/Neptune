/**
* @file VertexBuffer.h.
* @brief The VertexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D11/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/VertexBuffer.h"

namespace Neptune::Direct3D11 {

	/**
	* @brief Direct3D11::VertexBuffer Class.
	* This class defines the Direct3D11::VertexBuffer behaves.
	*/
	class VertexBuffer : public ContextAccessor, public RHI::RHIVertexBuffer::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit VertexBuffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~VertexBuffer() override = default;

	private:

	};
}

#endif