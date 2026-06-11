/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/Device.h"

namespace Neptune::Direct3D11 {

	using IDevice = IInfrastructure<class Device, EInfrastructure::Device>;

	/**
	* @brief Direct3D11::Device Class.
	* This class defines the Direct3D11::Device behaves.
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