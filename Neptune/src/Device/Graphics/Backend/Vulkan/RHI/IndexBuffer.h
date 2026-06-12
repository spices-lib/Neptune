/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Buffer.h"
#include "Device/Graphics/Frontend/RHI/IndexBuffer.h"

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