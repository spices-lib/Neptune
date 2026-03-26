/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/Instance.h"

namespace Neptune::Vulkan {

	/**
	* @brief Surface Class.
	*/
	class Surface : public Infrastructure
	{
	public:

		/**
		* @brief Mark as Surface Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::Surface;

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context The global Vulkan Context.
		*/
		Surface(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~Surface() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		* 
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkSurfaceKHR& Handle() { return m_Handle; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkSurfaceKHR.
		*/
		VkSurfaceKHR m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(Surface* infrastructure)
	{
		NEPTUNE_PROFILE_ZONE

		const auto instance = infrastructure->m_Context.Get<Instance>()->Handle();

		vkDestroySurfaceKHR(instance, infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}

#endif