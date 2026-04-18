/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/OpenGL/Core.h"
#include "Render/Backend/OpenGL/Unit/Buffer.h"
#include "Render/Frontend/RHI/IndexBuffer.h"

namespace Neptune::OpenGL {

	/**
	* @brief OpenGL::IndexBuffer Class.
	* This class defines the OpenGL::IndexBuffer behaves.
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

		Unit::Buffer m_Buffer;      // @brief This Buffer.
	};
}

#endif