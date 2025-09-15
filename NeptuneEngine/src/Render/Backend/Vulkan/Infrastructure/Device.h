/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {

	/**
	* @brief Device Class.
	*/
	class Device : public Infrastructure
	{
	public:

		/**
		* @brief Mark as Device Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::Device;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global Vulkan Context.
		*/
		Device(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~Device() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkDevice& Handle() { return m_Handle; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkDevice.
		*/
		VkDevice m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(Device* infrastructure)
	{
		vkDestroyDevice(infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}

#endif