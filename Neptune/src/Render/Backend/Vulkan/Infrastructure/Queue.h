#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Queue.h"

namespace Neptune::Vulkan {

	using IGraphicQueue     = InfrastructureClass<class Queue, EInfrastructure::GraphicQueue>;
	using IPresentQueue     = InfrastructureClass<class Queue, EInfrastructure::PresentQueue>;
	using IComputeQueue     = InfrastructureClass<class Queue, EInfrastructure::ComputeQueue>;

	class Queue : public Infrastructure
	{
	public:

		Queue(Context& context, EInfrastructure e, VkQueue queue);

		~Queue() override = default;

		void Init(Unit::Queue::Handle queue);

		const Unit::Queue::Handle& Handle() const { return m_Queue.GetHandle(); }

		void Submit(const VkSubmitInfo& info, VkFence fence = VK_NULL_HANDLE);

		void Wait();

	private:

		Unit::Queue m_Queue;
	};

}