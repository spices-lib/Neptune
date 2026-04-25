/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/CommandQueue.h"

namespace Neptune::Direct3D12::Unit {
	
	class Fence;
}

namespace Neptune::Direct3D12 {

	using IGraphicQueue     = IInfrastructure<class Queue, EInfrastructure::GraphicQueue>;
	using IComputeQueue     = IInfrastructure<class Queue, EInfrastructure::ComputeQueue>;

	/**
	* @brief Direct3D12::Queue Class.
	* This class defines the Direct3D12::Queue behaves.
	*/
	class Queue : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Queue(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Queue() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::CommandQueue::Handle& Handle() const { return m_Queue.GetHandle(); }

		/**
		* @brief Submit CommandList to Queue.
		* 
		* @param[in] commandList D3D12GraphicsCommandList.
		* @param[in] fence Unit::Fence.
		*/
		void Submit(D3D12GraphicsCommandList commandList, const SP<Unit::Fence>& fence = nullptr) const;

	private:

		/**
		* @brief Create CommandQueue.
		*/
		void Create();

		/**
		* @brief Get CommandListType.
		*
		* @return Returns CommandListType.
		*/
		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;

	private:

		Unit::CommandQueue m_Queue;    // @brief This Queue.
	};

}

#endif