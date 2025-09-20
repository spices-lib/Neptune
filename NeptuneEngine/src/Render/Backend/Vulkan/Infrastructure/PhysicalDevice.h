/**
* @file PhysicalDevice.h.
* @brief The PhysicalDevice Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {
	
	/**
	* @brief PhysicalDevice Class.
	*/
	class PhysicalDevice : public Infrastructure
	{
	public:

		/**
		* @brief Mark as PhysicalSurface Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::PhysicalSurface;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global Vulkan Context.
		*/
		PhysicalDevice(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~PhysicalDevice() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkPhysicalDevice& Handle() { return m_Handle; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief Check all Extension we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if all Extension we need meet.
		*/
		bool IsExtensionMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Check all Property we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if all Property we need meet.
		*/
		bool IsPropertyMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Check all  Feature we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if all Feature we need meet.
		*/
		bool IsFeatureMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Check all Queue we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		* 
		* @return Returns true if all Extension we need meet.
		*/
		bool IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

	private:

		/**
		* @brief VkPhysicalDevice.
		*/
		VkPhysicalDevice m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(PhysicalDevice* infrastructure)
	{
		NEPTUNE_PROFILE_ZONE

		infrastructure->Handle() = nullptr;
	}

}

#endif