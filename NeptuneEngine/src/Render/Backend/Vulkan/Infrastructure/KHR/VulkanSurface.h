/**
* @file VulkanSurface.h.
* @brief The VulkanSurface Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/VulkanInfrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/VulkanInstance.h"

namespace Neptune {

	/**
	* @brief VulkanSurface Class.
	*/
	class VulkanSurface : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanSurface Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanSurface;

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context The global VulkanContext.
		*/
		VulkanSurface(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanSurface() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		* 
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkSurfaceKHR& Row() { return m_Surface; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkSurfaceKHR.
		*/
		VkSurfaceKHR m_Surface = nullptr;

	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanSurface* infrastructure)
	{
		const auto instance = infrastructure->m_Context.Get<VulkanInstance>()->Row();

		vkDestroySurfaceKHR(instance, infrastructure->Row(), nullptr);
		infrastructure->Row() = nullptr;
	}

}

#endif