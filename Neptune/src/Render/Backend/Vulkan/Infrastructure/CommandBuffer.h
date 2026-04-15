/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"

#include <vector>

namespace Neptune::Vulkan {

	using IGraphicCommandBuffer     = InfrastructureClass<class CommandBuffer, EInfrastructure::GraphicCommandBuffer>;
	using IComputeCommandBuffer     = InfrastructureClass<class CommandBuffer, EInfrastructure::ComputeCommandBuffer>;

	/**
	* @brief Vulkan::CommandBuffer Class.
	* This class defines the Vulkan::CommandBuffer behaves.
	*/
	class CommandBuffer : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count CommandBuffer Counts.
		*/
		CommandBuffer(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~CommandBuffer() override = default;

		/**
		* @brief Get Unit Handle.
		* 
		* @param[in] index Handle index.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::CommandBuffer::Handle& Handle(uint32_t index = 0) const { return m_CommandBuffers[index]->GetHandle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @param[in] index Handle index.
		*
		* @return Returns Unit Handle Interface.
		*/
		const SP<Unit::CommandBuffer> IHandle(uint32_t index = 0) const { return m_CommandBuffers[index]; }

		/**
		* @brief Begin CommandBuffer.
		*
		* @param[in] info VkCommandBufferBeginInfo.
		* @param[in] index Handle index.
		*/
		void Begin(const VkCommandBufferBeginInfo& info, uint32_t index = 0) const;

		/**
		* @brief End CommandBuffer.
		*
		* @param[in] index Handle index.
		*/
		void End(uint32_t index = 0) const;

	private:

		/**
		* @brief Create CommandBuffer.
		*
		* @param[in] count CommandBuffer Counts.
		*/
		void Create(uint32_t count);

		/**
		* @brief Get Unit CommandPool Handle which allocated this CommandBuffer.
		*
		* @return Returns Unit CommandPool Handle which allocated this CommandBuffer.
		*/
		const VkCommandPool& GetCommandPool() const;

	private:

		std::vector<SP<Unit::CommandBuffer>> m_CommandBuffers;  // @brief Container of this unit CommandBuffer.

	};

}

#endif