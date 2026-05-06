/**
* @file VertexBuffer.h.
* @brief The VertexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Render/Frontend/RHI/VertexBuffer.h"

namespace Neptune::Direct3D12 {

	/**
	* @brief Direct3D12::VertexBuffer Class.
	* This class defines the Direct3D12::VertexBuffer behaves.
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