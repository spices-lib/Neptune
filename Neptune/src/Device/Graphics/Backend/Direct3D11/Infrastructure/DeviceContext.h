/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/DeviceContext.h"

namespace Neptune::Direct3D11::Unit {

	class Fence;
}

namespace Neptune::Direct3D11 {

	using IDeviceContext = IInfrastructure<class DeviceContext, EInfrastructure::DeviceContext>;

	/**
	* @brief Direct3D11::DeviceContext Class.
	* This class defines the Direct3D11::DeviceContext behaves.
	*/
	class DeviceContext : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		DeviceContext(Context& context, EInfrastructure e)
			: Infrastructure(context, e) {}

		/**
		* @brief Destructor Function.
		*/
		~DeviceContext() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::DeviceContext::Handle& Handle() const { return m_DeviceContext.GetHandle(); }

		/**
		* @brief Set Unit Handle.
		* 
		* @param[in] handle Unit::DeviceContext::Handle.
		*/
		void SetHandle(Unit::DeviceContext::Handle handle);

		/**
		* @brief Single Fence.
		*
		* @param[in] fence Unit::Fence.
		*/
		void Signal(const SP<Unit::Fence>& fence) const;

	private:

		Unit::DeviceContext m_DeviceContext;   // @brief this DeviceContext.
	};

}

#endif