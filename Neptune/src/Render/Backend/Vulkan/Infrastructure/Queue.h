/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Queue.h"

namespace Neptune::Vulkan {

	using IGraphicQueue     = IInfrastructure<class Queue, EInfrastructure::GraphicQueue>;
	using IPresentQueue     = IInfrastructure<class Queue, EInfrastructure::PresentQueue>;
	using IComputeQueue     = IInfrastructure<class Queue, EInfrastructure::ComputeQueue>;

	/**
	* @brief Vulkan::Queue Class.
	* This class defines the Vulkan::Queue behaves.
	*/
	class Queue : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] queue VkQueue.
		*/
		Queue(Context& context, EInfrastructure e, VkQueue queue);

		/**
		* @brief Destructor Function.
		*/
		~Queue() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Queue::Handle& Handle() const { return m_Queue.GetHandle(); }

		/**
		* @brief Submit CommandBuffer to Queue.
		*
		* @param[in] info VkSubmitInfo.
		* @param[in] fence VkFence.
		*/
		void Submit(const VkSubmitInfo& info, VkFence fence = VK_NULL_HANDLE) const;

		/**
		* @brief Queue Wait idle.
		*/
		void Wait() const;

	private:

		/**
		* @brief Initialize with queue.
		*
		* @param[in] queue Unit Queue Handle.
		*/
		void Init(Unit::Queue::Handle queue);

	private:

		Unit::Queue m_Queue;    // @brief This Queue.
	};

}

#endif