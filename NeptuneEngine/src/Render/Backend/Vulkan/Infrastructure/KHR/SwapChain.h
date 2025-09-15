/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"

namespace Neptune::Vulkan {

	/**
	* @brief SwapChain Class.
	*/
	class SwapChain : public Infrastructure
	{
	public:

		/**
		* @brief Mark as SwapChain Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::SwapChain;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global Vulkan Context.
		*/
		SwapChain(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkSwapchainKHR& Handle() { return m_Handle; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkSwapchainKHR.
		*/
		VkSwapchainKHR m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(SwapChain* infrastructure)
	{
		const auto device = infrastructure->m_Context.Get<Device>()->Handle();

		vkDestroySwapchainKHR(device, infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}

#endif