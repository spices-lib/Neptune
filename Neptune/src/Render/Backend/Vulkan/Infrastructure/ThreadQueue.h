/**
* @file ThreadQueue.h.
* @brief The ThreadQueue Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Queue.h"
#include "Core/Container/ThreadQueue.hpp"

namespace Neptune::Vulkan {

	using IGraphicThreadQueue     = InfrastructureClass<class ThreadQueue, EInfrastructure::GraphicThreadQueue>;
	using IComputeThreadQueue     = InfrastructureClass<class ThreadQueue, EInfrastructure::ComputeThreadQueue>;
	using ITransferThreadQueue    = InfrastructureClass<class ThreadQueue, EInfrastructure::TransferThreadQueue>;
	using IVideoEncodeThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::VideoEncodeThreadQueue>;
	using IVideoDecodeThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::VideoDecodeThreadQueue>;
	using IOpticalFlowThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::OpticalFlowThreadQueue>;

	/**
	* @brief Vulkan::ThreadQueue Class.
	* This class defines the Vulkan::ThreadQueue behaves.
	*/
	class ThreadQueue : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		ThreadQueue(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~ThreadQueue() override = default;

		/**
		* @brief Pop a Queue.
		* 
		* @return Returns Queue.
		*/
		SP<Unit::Queue> Pop() { return m_Queues.Pop(); }

		/**
		* @brief Push a Queue.
		*
		* @param[in] queue Queue.
		*/
		void Push(SP<Unit::Queue> queue) { m_Queues.Push(queue); }

		/**
		* @brief Add a Queue to this.
		*
		* @param[in] handle Queue.
		*/
		void Add(Unit::Queue::Handle handle);

	private:

		Container::ThreadQueue<SP<Unit::Queue>> m_Queues;   // @brief Container of Queue.

	};
	
}

#endif