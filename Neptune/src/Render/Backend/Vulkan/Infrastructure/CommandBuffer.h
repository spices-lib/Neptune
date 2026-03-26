#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include <vector>

namespace Neptune::Vulkan {

	using IGraphicCommandBuffer     = InfrastructureClass<class CommandBuffer, EInfrastructure::GraphicCommandBuffer>;
	using IComputeCommandBuffer     = InfrastructureClass<class CommandBuffer, EInfrastructure::ComputeCommandBuffer>;

	class CommandBuffer : public Infrastructure
	{
	public:

		CommandBuffer(Context& context, EInfrastructure e, uint32_t count = 1);

		~CommandBuffer() override = default;

		const Unit::CommandBuffer::Handle& Handle(uint32_t index = 0) { return m_CommandBuffers[index]->GetHandle(); }

		SP<Unit::CommandBuffer> IHandle(uint32_t index = 0) { return m_CommandBuffers[index]; }

		void Begin(const VkCommandBufferBeginInfo& info, uint32_t index = 0) const;

		void End(uint32_t index = 0) const;

	private:

		void Create(uint32_t count);

		const VkCommandPool& GetCommandPool();

	private:

		std::vector<SP<Unit::CommandBuffer>> m_CommandBuffers;

	};

}