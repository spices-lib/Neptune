#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Queue.h"
#include "Core/Container/ThreadQueue.hpp"

namespace Neptune::Vulkan {

	using IGraphicThreadQueue     = InfrastructureClass<class ThreadQueue, EInfrastructure::GraphicThreadQueue>;
	using IComputeThreadQueue     = InfrastructureClass<class ThreadQueue, EInfrastructure::ComputeThreadQueue>;
	using ITransferThreadQueue    = InfrastructureClass<class ThreadQueue, EInfrastructure::TransferThreadQueue>;
	using IVideoEncodeThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::VideoEncodeThreadQueue>;
	using IVideoDecodeThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::VideoDecodeThreadQueue>;
	using IOpticalFlowThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::OpticalFlowThreadQueue>;

	class ThreadQueue : public Infrastructure
	{
	public:

		ThreadQueue(Context& context, EInfrastructure e);

		~ThreadQueue() override = default;

		SP<Unit::Queue> Pop() { return m_Queues.Pop(); }

		void Push(SP<Unit::Queue> queue) { m_Queues.Push(queue); }

		void Add(VkQueue handle);

	private:

		Container::ThreadQueue<SP<Unit::Queue>> m_Queues;

	};
	
}