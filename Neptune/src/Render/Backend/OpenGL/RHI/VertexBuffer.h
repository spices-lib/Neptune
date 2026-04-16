/**
* @file VertexBuffer.h.
* @brief The VertexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/OpenGL/Core.h"
#include "Render/Backend/OpenGL/Unit/VertexArray.h"
#include "Render/Frontend/RHI/VertexBuffer.h"

namespace Neptune::OpenGL {

	/**
	* @brief Vulkan::VertexBuffer Class.
	* This class defines the OpenGL::VertexBuffer behaves.
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

		Unit::VertexArray m_Buffer;            // @brief This Buffer.
	};
}

#endif