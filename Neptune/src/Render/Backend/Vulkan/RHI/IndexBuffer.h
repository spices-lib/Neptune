/**
* @file IndexBuffer.h.
* @brief The IndexBuffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"
#include "Render/Frontend/RHI/IndexBuffer.h"

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