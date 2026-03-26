#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include <array>

namespace Neptune::Vulkan {

    class Infrastructure;

    enum class EInfrastructure : uint8_t
    {
        Functions = 0,
        Instance,
        DebugUtilsObject,
        Surface,
        PhysicalDevice,
        Device,

        GraphicQueue,
        PresentQueue,
        ComputeQueue,

        GraphicThreadQueue,
        ComputeThreadQueue,
        TransferThreadQueue,
        VideoEncodeThreadQueue,
        VideoDecodeThreadQueue,
        OpticalFlowThreadQueue,

        MemoryAllocator,
        SwapChain,

        GraphicImageSemaphore,
        GraphicQueueSemaphore,
        GraphicFence,

        ComputeQueueSemaphore,
        ComputeFence,

        GraphicCommandPool,
        GraphicCommandBuffer,

        ComputeCommandPool,
        ComputeCommandBuffer,

        GraphicThreadCommandPool,
        ComputeThreadCommandPool,
        TransferThreadCommandPool,
        VideoEncodeThreadCommandPool,
        VideoDecodeThreadCommandPool,
        OpticalFlowThreadCommandPool,

        DescriptorPool,

        Count
    };

    template<typename T_, EInfrastructure E_>
	struct InfrastructureClass
	{
		using T = T_;
        static constexpr EInfrastructure E = E_;
	};

    class Context : NonCopyable
    {
    public:

        Context() = default;

        ~Context() override = default;

        template<typename I, typename... Args>
        void Registry(Args&&... args);

        template<typename I>
        void UnRegistry();

        void UnRegistry();

        template<typename I>
        SP<typename I::T> Get();

        template<typename I>
        bool Has() const;

    private:

        std::array<SP<Infrastructure>, static_cast<uint8_t>(EInfrastructure::Count)> m_Infrastructures;
    };

    template<typename I, typename... Args>
    void Context::Registry(Args&&... args)
    {
        const auto position = static_cast<uint8_t>(I::E);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure already registered.")
        }

        m_Infrastructures[position] = CreateSP<typename I::T>(*this, I::E, std::forward<Args>(args)...);
    }

    template <typename I>
    inline void Context::UnRegistry()
    {
        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure is not registered, can not be unregister")

            return;
        }

        m_Infrastructures[position].reset();
    }

    inline void Context::UnRegistry()
    {
        for (int i = static_cast<int>(EInfrastructure::Count) - 1; i >= 0; i--)
        {
            if (!m_Infrastructures[i])
            {
                NEPTUNE_CORE_ERROR("Vulkan Infrastructure is not registered, can not be unregister")

                continue;
            }

            m_Infrastructures[i].reset();
        }
    }

    template<typename I>
    SP<typename I::T> Context::Get()
    {
        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure is not registered, can not be got")

            return nullptr;
        }

        return std::dynamic_pointer_cast<typename I::T>(m_Infrastructures[position]);
    }

    template<typename I>
    bool Context::Has() const
    {
        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }

}