/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "GPURuntime/Graphics/Backend/Direct3D11/Infrastructure/Infrastructure.h"
#include "GPURuntime/Graphics/Frontend/RHI/IndexBuffer.h"

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