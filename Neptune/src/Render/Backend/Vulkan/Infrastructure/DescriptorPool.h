#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/DescriptorPool.h"
#include <vector>

namespace Neptune::Vulkan {

	using IDescriptorPool = InfrastructureClass<class DescriptorPool, EInfrastructure::DescriptorPool>;

	class DescriptorPool : public Infrastructure
	{
	public:

		DescriptorPool(Context& context, EInfrastructure e);

		~DescriptorPool() override = default;

		const Unit::DescriptorPool::Handle& Handle() const { return m_DescriptorPool.GetHandle(); }

	private:

		void Create();

	private:

		Unit::DescriptorPool m_DescriptorPool;

	};

}