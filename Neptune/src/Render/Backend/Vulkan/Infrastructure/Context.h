/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include <array>

namespace Neptune::Vulkan {

    class Infrastructure;

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        Functions = 0,                       // @brief Functors.
        Instance,                            // @brief Instance.
        DebugUtilsObject,                    // @brief Label/Name Functors.
        Surface,                             // @brief Surface.
        PhysicalDevice,                      // @brief PhysicalDevice.
        Device,                              // @brief LogicalDevice.
                                             
        GraphicQueue,                        // @brief Main Thread Graphic Queue.
        PresentQueue,                        // @brief Main Thread Present Queue.
        ComputeQueue,                        // @brief Main Thread Compute Queue.

        GraphicThreadQueue,                  // @brief Sub Thread Graphic Queue.
        ComputeThreadQueue,                  // @brief Sub Thread Compute Queue.
        TransferThreadQueue,                 // @brief Sub Thread Transfer Queue.
        VideoEncodeThreadQueue,              // @brief Sub Thread VideoEncode Queue.
        VideoDecodeThreadQueue,              // @brief Sub Thread VideoDecode Queue.
        OpticalFlowThreadQueue,              // @brief Sub Thread OpticalFlow Queue.
                                             
        MemoryAllocator,                     // @brief VMA.
        SwapChain,                           // @brief SwapChain.
                                             
        GraphicImageSemaphore,               // @brief Main Thread Graphic ImageSemaphore.
        GraphicQueueSemaphore,               // @brief Main Thread Graphic QueueSemaphore.
        GraphicFence,                        // @brief Main Thread Graphic Fence.
                                             
        ComputeQueueSemaphore,               // @brief Main Thread Compute QueueSemaphore.
        ComputeFence,                        // @brief Main Thread Compute Fence.
                                             
        GraphicCommandPool,                  // @brief Main Thread Graphic CommandPool.
        GraphicCommandBuffer,                // @brief Main Thread Graphic CommandBuffer.

        ComputeCommandPool,                  // @brief Main Thread Compute CommandPool.
        ComputeCommandBuffer,                // @brief Main Thread Compute CommandBuffer.

        GraphicThreadCommandPool,            // @brief Sub Thread Graphic CommandPool.
        ComputeThreadCommandPool,            // @brief Sub Thread Compute CommandPool.
        TransferThreadCommandPool,           // @brief Sub Thread Transfer CommandPool.
        VideoEncodeThreadCommandPool,        // @brief Sub Thread VideoEncode CommandPool.
        VideoDecodeThreadCommandPool,        // @brief Sub Thread VideoDecode CommandPool.
        OpticalFlowThreadCommandPool,        // @brief Sub Thread OpticalFlow CommandPool.

        DescriptorPool,                      // @brief DescriptorPool.

        Count
    };

    /**
    * @brief Template of Infrastructure Class Definitions.
    * 
    * @tparam T_ Infrastructure Class.
    * @tparam E_ EInfrastructure.
    */
    template<typename T_, EInfrastructure E_>
	struct InfrastructureClass
	{
		using T = T_;
        static constexpr EInfrastructure E = E_;
	};

    /**
    * @brief Infrastructure Factory.
    *
    * @tparam T Specification of Infrastructure.
    * @param[in] args Infrastructure Params.
    * 
    * @return Returns Infrastructure.
    */
    template<typename T, typename... Args>
    static SP<T> InfrastructureFactory(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE
        
        if constexpr (requires(Args... args) {
            { T::Create(std::forward<Args>(args)...) } -> std::same_as<SP<T>>;
        })
        {
            // Factory Version
            return T::Create(std::forward<Args>(args)...);
        }
        else
        {
            // Directory Version
            return CreateSP<T>(std::forward<Args>(args)...);
        }
    }
    
    /**
    * @brief RenderBackend Context.
    */
    class Context : NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Context() = default;

        /**
        * @brief Destructor Function.
        */
        ~Context() override = default;

        /**
        * @brief Registry Infrastructure.
        *
        * @tparam I Infrastructure Definitions.
        * @param[in] args Infrastructure Construct Params.
        */
        template<typename I, typename... Args>
        void Registry(Args&&... args);

        /**
        * @brief Unregister Infrastructure.
        *
        * @tparam I Infrastructure Definitions.
        */
        template<typename I>
        void UnRegistry();

        /**
        * @brief Unregister All Infrastructure.
        */
        void UnRegistry();

        /**
        * @brief Get registry Infrastructure.
        *
        * @tparam I Infrastructure Definitions.
        * 
        * @return Returns registry Infrastructure.
        */
        template<typename I>
        I::T* Get();

        /**
        * @brief Is Infrastructure registry.
        *
        * @tparam I Infrastructure Definitions.
        *
        * @return Returns true if registry.
        */
        template<typename I>
        bool Has() const;

    private:

        std::array<SP<Infrastructure>, static_cast<uint8_t>(EInfrastructure::Count)> m_Infrastructures; // @brief Container of Infrastructure.

    };

    template<typename I, typename... Args>
    inline void Context::Registry(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure Already Registered.")

            return;
        }

        m_Infrastructures[position] = InfrastructureFactory<typename I::T>(*this, I::E, std::forward<Args>(args)...);
    }

    template <typename I>
    inline void Context::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure is not registered yet, can not be unregisted.")

            return;
        }

        m_Infrastructures[position].reset();
    }

    inline void Context::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        for (int i = static_cast<int>(EInfrastructure::Count) - 1; i >= 0; i--)
        {
            if (!m_Infrastructures[i])
            {
                NEPTUNE_CORE_ERROR("Vulkan Infrastructure is not registered yet, can not be unregisted.")

                continue;
            }

            m_Infrastructures[i].reset();
        }
    }

    template<typename I>
    I::T* Context::Get()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position])
        {
            NEPTUNE_CORE_ERROR("Vulkan Infrastructure is not registered yet, can not be got.")

            return nullptr;
        }

        return std::dynamic_pointer_cast<typename I::T>(m_Infrastructures[position]).get();
    }

    template<typename I>
    bool Context::Has() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }

}