/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {

	/**
	* @brief Instance Class.
	*/
	class Instance : public Infrastructure
	{
	public:

		/**
		* @brief Mark as Instance Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::Instance;

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context The global Vulkan Context.
		*/
		Instance(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~Instance() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		* 
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkInstance& Handle() { return m_Handle; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkInstance
		*/
		VkInstance m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(Instance* infrastructure)
	{
		vkDestroyInstance(infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}

#endif