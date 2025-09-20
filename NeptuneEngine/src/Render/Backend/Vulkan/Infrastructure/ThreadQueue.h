/**
* @file ThreadQueue.h.
* @brief The ThreadQueue Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {

	/**
	* @brief ThreadQueue Class.
	*/
	class ThreadQueue : public Infrastructure
	{
	public:

		/**
		* @brief Mark as ThreadQueue Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::ThreadQueue;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global Vulkan Context.
		*/
		ThreadQueue(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~ThreadQueue() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkQueue& Handle() { return m_Handle; }

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
		VkQueue m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(ThreadQueue* infrastructure)
	{
		NEPTUNE_PROFILE_ZONE

		infrastructure->Handle() = nullptr;
	}

}

#endif