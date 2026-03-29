/**
* @file ThreadCommandPool.cpp.
* @brief The ThreadCommandPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ThreadCommandPool.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

	namespace {
	
		/**
		* @brief Thread CommandPool Thread ID.
		*/
		class ThreadID
		{
		public:

			/**
			* @brief Constructor Function.
			*/
			ThreadID() = default;

			/**
			* @brief Destructor Function.
			*/
			virtual ~ThreadID()
			{
				auto commandPool = m_Guard.lock();

				if (!commandPool)
				{
					return;
				}

				if (m_GraphicId.has_value())     commandPool->Release(m_GraphicId.value());
				if (m_ComputeId.has_value())     commandPool->Release(m_ComputeId.value());
				if (m_TransferId.has_value())    commandPool->Release(m_TransferId.value());
				if (m_VideoEncodeId.has_value()) commandPool->Release(m_VideoEncodeId.value());
				if (m_VideoDecodeId.has_value()) commandPool->Release(m_VideoDecodeId.value());
				if (m_OpticalFlowId.has_value()) commandPool->Release(m_OpticalFlowId.value());
			}

			/**
			* @brief Get Thread CommandPool id.
			* 
			* @param[in] e EInfrastructure.
			* 
			* @return Returns Thread CommandPool id.
			*/
			const std::optional<UUID>& Id(EInfrastructure e) const
			{
				switch (e)
				{
					case EInfrastructure::GraphicThreadCommandPool:     return m_GraphicId;
					case EInfrastructure::ComputeThreadCommandPool:     return m_ComputeId;
					case EInfrastructure::TransferThreadCommandPool:    return m_TransferId;
					case EInfrastructure::VideoEncodeThreadCommandPool: return m_VideoEncodeId;
					case EInfrastructure::VideoDecodeThreadCommandPool: return m_VideoDecodeId;
					case EInfrastructure::OpticalFlowThreadCommandPool: return m_OpticalFlowId;
					default: return std::nullopt;
				}
			}

			/**
			* @brief Set Thread CommandPool id.
			*
			* @param[in] id Thread CommandPool id.
			* @param[in] e EInfrastructure.
			*/
			void SetId(const UUID& id, EInfrastructure e)
			{
				switch (e)
				{
					case EInfrastructure::GraphicThreadCommandPool:     m_GraphicId     = id; return;
					case EInfrastructure::ComputeThreadCommandPool:     m_ComputeId     = id; return;
					case EInfrastructure::TransferThreadCommandPool:    m_TransferId    = id; return;
					case EInfrastructure::VideoEncodeThreadCommandPool: m_VideoEncodeId = id; return;
					case EInfrastructure::VideoDecodeThreadCommandPool: m_VideoDecodeId = id; return;
					case EInfrastructure::OpticalFlowThreadCommandPool: m_OpticalFlowId = id; return;
					default: return;
				}
			}

			/**
			* @brief Set CommandPool Guard.
			*
			* @param[in] guard Thread CommandPool.
			*/
			void SetGuard(SP<ThreadCommandPool> guard)
			{
				m_Guard = guard;
			}

		public:

			std::optional<UUID> m_GraphicId;            // @brief Graphic Sub Thread CommandPool id.
			std::optional<UUID> m_ComputeId;            // @brief Compute Sub Thread CommandPool id.
			std::optional<UUID> m_TransferId;           // @brief Transfer Sub Thread CommandPool id.
			std::optional<UUID> m_VideoEncodeId;        // @brief VideoEncode Sub Thread CommandPool id.
			std::optional<UUID> m_VideoDecodeId;        // @brief VideoDecode Sub Thread CommandPool id.
			std::optional<UUID> m_OpticalFlowId;        // @brief OpticalFlow Sub Thread CommandPool id.

			WP<ThreadCommandPool> m_Guard;              // @brief ThreadCommandPool Guard.
		};

		_declspec(thread) ThreadID s_TLSThreadID;       // @brief Thread id instance.

		std::mutex s_Mutex;                             // @brief CommandPool mutex.
	}

	ThreadCommandPool::ThreadCommandPool(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{}

	const VkCommandPool& ThreadCommandPool::Handle()
	{
		NEPTUNE_PROFILE_ZONE

		auto id = s_TLSThreadID.Id(GetEInfrastructure());

		if (id.has_value())
		{
			return m_CommandPools[id.value()]->GetHandle();
		}

		UUID uuid;

		s_TLSThreadID.SetId(uuid, GetEInfrastructure());

		s_TLSThreadID.SetGuard(shared_from_this());

		auto commandPool = Create();

		std::unique_lock lock(s_Mutex);

		m_CommandPools[uuid] = commandPool;

		return commandPool->GetHandle();
	}

	void ThreadCommandPool::Release(UUID id)
	{
		NEPTUNE_PROFILE_ZONE

		std::unique_lock lock(s_Mutex);

		m_CommandPools.erase(id);
	}

	SP<Unit::CommandPool> ThreadCommandPool::Create() const
	{
		NEPTUNE_PROFILE_ZONE

		VkCommandPoolCreateInfo                   poolInfo{};
		poolInfo.sType                          = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags                          = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex               = GetQueueFamily();

		auto commandPool = CreateSP<Unit::CommandPool>();

		commandPool->CreateCommandPool(GetContext().Get<IDevice>()->Handle(), poolInfo);

		DEBUGUTILS_SETOBJECTNAME(*commandPool, ToString())

		return commandPool;
	}

	uint32_t ThreadCommandPool::GetQueueFamily() const
	{
		NEPTUNE_PROFILE_ZONE

		switch (GetEInfrastructure())
		{
			case EInfrastructure::GraphicThreadCommandPool:		return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value();
			case EInfrastructure::ComputeThreadCommandPool:     return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().compute.value();
			case EInfrastructure::TransferThreadCommandPool:    return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().transfer.value();
			case EInfrastructure::VideoEncodeThreadCommandPool: return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().videoEncode.value();
			case EInfrastructure::VideoDecodeThreadCommandPool: return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().videoDecode.value();
			case EInfrastructure::OpticalFlowThreadCommandPool: return GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().opticalFlow.value();
			default: return 0;
		}
	}
}