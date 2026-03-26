#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Device.h"

namespace Neptune::Vulkan {

	using IDevice = InfrastructureClass<class Device, EInfrastructure::Device>;

	class Device : public Infrastructure
	{
	public:

		Device(Context& context, EInfrastructure e);

		~Device() override = default;

		const Unit::Device::Handle& Handle() const { return m_Device.GetHandle(); }

		void Wait();

	private:

		void Create();

	private:

		Unit::Device m_Device;

	};
}