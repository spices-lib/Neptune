/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "GPURuntime/Graphics/Backend/Vulkan/Unit/Buffer.h"
#include "GPURuntime/Graphics/Frontend/RHI/IndexBuffer.h"

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::IndexBuffer Class.
	* This class defines the Vulkan::IndexBuffer behaves.
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