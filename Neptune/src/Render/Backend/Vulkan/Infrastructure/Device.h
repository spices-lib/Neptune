/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Device.h"

namespace Neptune::Vulkan {

	using IDevice = InfrastructureClass<class Device, EInfrastructure::Device>;

	/**
	* @brief Vulkan::Device Class.
	* This class defines the Vulkan::Device behaves.
	*/
	class Device : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Device(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Device() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Device::Handle& Handle() const { return m_Device.GetHandle(); }

		/**
		* @brief Device wait idle.
		*/
		void Wait() const;

	private:

		/**
		* @brief Create Device.
		*/
		void Create();

	private:

		Unit::Device m_Device; // @brief this Device.

	};
}

#endif