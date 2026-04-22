/**
* @file ThreadCommandPool.h.
* @brief The ThreadCommandPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandPool.h"
#include "Core/UUID.h"

#include <unordered_map>

namespace Neptune::Vulkan {

	using IGraphicThreadCommandPool     = IInfrastructure<class ThreadCommandPool, EInfrastructure::GraphicThreadCommandPool>;
	using IComputeThreadCommandPool     = IInfrastructure<class ThreadCommandPool, EInfrastructure::ComputeThreadCommandPool>;
	using ITransferThreadCommandPool    = IInfrastructure<class ThreadCommandPool, EInfrastructure::TransferThreadCommandPool>;
	using IVideoEncodeThreadCommandPool = IInfrastructure<class ThreadCommandPool, EInfrastructure::VideoEncodeThreadCommandPool>;
	using IVideoDecodeThreadCommandPool = IInfrastructure<class ThreadCommandPool, EInfrastructure::VideoDecodeThreadCommandPool>;
	using IOpticalFlowThreadCommandPool = IInfrastructure<class ThreadCommandPool, EInfrastructure::OpticalFlowThreadCommandPool>;

	/**
	* @brief Vulkan::ThreadCommandPool Class.
	* This class defines the Vulkan::ThreadCommandPool behaves.
	*/
	class ThreadCommandPool : public Infrastructure, public std::enable_shared_from_this<ThreadCommandPool>
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		ThreadCommandPool(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~ThreadCommandPool() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::CommandPool::Handle& Handle();

		/**
		* @brief Release CommandPool Unit..
		*
		* @param[in] id CommandPool Id.
		*/
		void Release(UUID id);

	private:

		/**
		* @brief Create CommandPool.
		*
		* @return Returns CommandPool.
		*/
		SP<Unit::CommandPool> Create() const;

		/**
		* @brief Get CommandPool QueueFamily.
		*
		* @return Returns CommandPool QueueFamily.
		*/
		uint32_t GetQueueFamily() const;

	private:

		std::unordered_map<UUID, SP<Unit::CommandPool>> m_CommandPools;    // @brief Container of CommandPool.
	};

}

#endif