/**
* @file VulkanInstance.h.
* @brief The VulkanInstance Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanInfrastructure.h"

namespace Neptune {

	/**
	* @brief VulkanInstance Class.
	*/
	class VulkanInstance : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanInstance Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanInstance;

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context The global VulkanContext.
		*/
		VulkanInstance(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanInstance() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		* 
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkInstance& Row() { return m_Instance; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkInstance
		*/
		VkInstance m_Instance = nullptr;

	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanInstance* infrastructure)
	{
		vkDestroyInstance(infrastructure->Row(), nullptr);
		infrastructure->Row() = nullptr;
	}

}

#endif