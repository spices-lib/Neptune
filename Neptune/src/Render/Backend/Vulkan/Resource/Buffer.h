/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"

namespace Neptune::Vulkan {

	/**
	* @brief Vulkan::Buffer Class.
	* This class defines the Vulkan::Buffer behaves.
	*/
	class Buffer : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Buffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Buffer() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Buffer::Handle& Handle() const { return m_Buffer.GetHandle(); }

		/**
		* @brief Get Buffer Size.
		*
		* @return Returns Buffer Size.
		*/
		const VkDeviceSize& Size() const { return m_Buffer.Size(); }

		/**
		* @brief Get Buffer Host Data.
		*
		* @return Returns Buffer Host Data.
		*/
		void* Data() const { return m_Buffer.HostMemory(); }

		/**
		* @brief Create Buffer.
		*
		* @param[in] capabilities VkBufferCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateBuffer(const VkBufferCreateInfo& capabilities, VkMemoryPropertyFlags properties);

		/**
		* @brief Write host data to Buffer.
		*
		* @param[in] data Host data.
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		void WriteToBuffer(const void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size Buffer size.
		* @param[in] offset Buffer offset.
		*/
		void Flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		/**
		* @brief Set Buffer name.
		*
		* @param[in] name Buffer name.
		*/
		void SetName(const std::string& name) const;

	private:

		Unit::Buffer m_Buffer;       // @brief This Buffer.
	};
}

#endif