/**
* @file VulkanThreadQueue.h.
* @brief The VulkanThreadQueue Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanInfrastructure.h"

namespace Neptune {

	/**
	* @brief VulkanThreadQueue Class.
	*/
	class VulkanThreadQueue : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanThreadQueue Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanThreadQueue;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global VulkanContext.
		*/
		VulkanThreadQueue(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanThreadQueue() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkQueue& Row() { return m_Queue; }

	public:

		/**
		* @brief Submit the CommandBuffer in this Queue.
* 
		* @param[in] commandBuffer VkCommandBuffer.
		*/
		void Submit(VkCommandBuffer commandBuffer) const;

		/**
		* @brief Wait for queue execute.
		*/
		void Wait() const;

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief Thread VkQueue.
		*/
		VkQueue m_Queue = nullptr;

	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanThreadQueue* infrastructure)
	{
		infrastructure->Row() = nullptr;
	}

}

#endif