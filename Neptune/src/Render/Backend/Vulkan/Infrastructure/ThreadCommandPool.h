#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandPool.h"
#include "Core/UUID.h"
#include <unordered_map>

namespace Neptune::Vulkan {

	using IGraphicThreadCommandPool     = InfrastructureClass<class ThreadCommandPool, EInfrastructure::GraphicThreadCommandPool>;
	using IComputeThreadCommandPool     = InfrastructureClass<class ThreadCommandPool, EInfrastructure::ComputeThreadCommandPool>;
	using ITransferThreadCommandPool    = InfrastructureClass<class ThreadCommandPool, EInfrastructure::TransferThreadCommandPool>;
	using IVideoEncodeThreadCommandPool = InfrastructureClass<class ThreadCommandPool, EInfrastructure::VideoEncodeThreadCommandPool>;
	using IVideoDecodeThreadCommandPool = InfrastructureClass<class ThreadCommandPool, EInfrastructure::VideoDecodeThreadCommandPool>;
	using IOpticalFlowThreadCommandPool = InfrastructureClass<class ThreadCommandPool, EInfrastructure::OpticalFlowThreadCommandPool>;

	class ThreadCommandPool : public Infrastructure, public std::enable_shared_from_this<ThreadCommandPool>
	{
	public:

		ThreadCommandPool(Context& context, EInfrastructure e);

		~ThreadCommandPool() override = default;

		const Unit::CommandPool::Handle& Handle();

		void Release(UUID id);

	private:

		SP<Unit::CommandPool> Create();

		uint32_t GetQueueFamily();

	private:

		std::unordered_map<UUID, SP<Unit::CommandPool>> m_CommandPools;
	};

}