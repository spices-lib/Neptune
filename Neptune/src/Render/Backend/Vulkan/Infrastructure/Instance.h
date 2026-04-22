/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Instance.h"

#include <vector>

namespace Neptune::Vulkan {

	using IInstance = IInfrastructure<class Instance, EInfrastructure::Instance>;

	/**
	* @brief Vulkan::Instance Class.
	* This class defines the Vulkan::Instance behaves.
	*/
	class Instance : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] windodExtensions Windod Extensions.
		*/
		Instance(Context& context, EInfrastructure e, const std::vector<const char*>&  windodExtensions);

		/**
		* @brief Destructor Function.
		*/
		~Instance() override;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Instance::Handle& Handle() const { return m_Instance.GetHandle(); }

		/**
		* @brief Get VkDebugUtilsMessengerEXT.
		*
		* @return Returns VkDebugUtilsMessengerEXT.
		*/
		const VkDebugUtilsMessengerEXT& DebugMessenger() const { return m_DebugMessenger; }

	private:

		/**
		* @brief Create Instance.
		*/
		void Create();

		/**
		* @brief Get Extension Requirements.
		*/
		void GetExtensionRequirements();

		/**
		* @brief Check Extension Requirements Satisfied.
		*/
		bool CheckExtensionRequirementsSatisfied();

		/**
		* @brief Get Layer Requirements.
		*/
		void GetLayerRequirements();

		/**
		* @brief Check Layer Requirements Satisfied.
		*/
		bool ChecklayerRequirementsSatisfied();

		/**
		* @brief Set DebugCallback.
		*/
		void SetVulkanDebugCallbackFuncPointer();

		/**
		* @brief Fill VkDebugUtilsMessengerCreateInfoEXT.
		*/
		void FillDebugMessengerCreateInfo();

	private:

		Unit::Instance m_Instance;                                             // @brief This Instance.
		std::vector<const char*> m_ExtensionProperties;                        // @brief Extensions.
		std::vector<const char*> m_LayerProperties;                            // @brief Layers.
		VkDebugUtilsMessengerEXT m_DebugMessenger{};                           // @brief VkDebugUtilsMessengerEXT.
		VkDebugUtilsMessengerCreateInfoEXT m_DebugMessengerCreateInfo{};       // @brief VkDebugUtilsMessengerCreateInfoEXT.
	};

}

#endif