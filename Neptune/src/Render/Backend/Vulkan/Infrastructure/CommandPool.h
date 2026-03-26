#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandPool.h"

namespace Neptune::Vulkan {

	using IGraphicCommandPool     = InfrastructureClass<class CommandPool, EInfrastructure::GraphicCommandPool>;
	using IComputeCommandPool     = InfrastructureClass<class CommandPool, EInfrastructure::ComputeCommandPool>;

	class CommandPool : public Infrastructure
	{
	public:

		CommandPool(Context& context, EInfrastructure e);

		~CommandPool() override = default;

		const Unit::CommandPool::Handle& Handle() { return m_CommandPool.GetHandle(); }

	private:

		void Create();

		uint32_t GetQueueFamily();

	private:

		Unit::CommandPool m_CommandPool;

	};

}