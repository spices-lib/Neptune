/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/Device.h"

namespace Neptune::Direct3D12 {

	using IDevice = IInfrastructure<class Device, EInfrastructure::Device>;

	/**
	* @brief Direct3D12::Device Class.
	* This class defines the Direct3D12::Device behaves.
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
		~Device() override;

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

		/**
		* @brief Get Device Max FeatureLevel.
		* 
		* @param[in] adapter DXGIAdapter.
		* 
		* @return Returns D3D_FEATURE_LEVEL.
		*/
		D3D_FEATURE_LEVEL GetMaxFeatureLevel(DXGIAdapter adapter) const;

	private:

		Unit::Device m_Device;           // @brief this Device.
	};
	
}

#endif