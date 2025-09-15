/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::WebGPU {

    /**
    * @brief Instance Class.
    */
    class Instance : public Infrastructure<WGPUInstance, EInfrastructure::Instance>
    {
    public:

        /**
        * @brief Mark as Instance Infrastructure Type.
        */
        static constexpr EInfrastructure Type = Infrastructure<WGPUInstance, EInfrastructure::Instance>::Type;
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] context The global WebGPU Context.
        */
        explicit Instance(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~Instance() override = default;

        /**
        * @brief Execute future and wait for done or timeout.
        *
        * @param[in] future WGPUFuture.
        */
        void Wait(const WGPUFuture& future);

        /**
        * @brief Create WebGPU Surface.
        *
        * @param[in] htmlCanvas HTML Canvas id.
        *
        * @return Returns WGPUSurface.
        */
        WGPUSurface CreateSurface(const std::string& htmlCanvas);

        /**
        * @brief Request WGPUAdapter.
        *
        * @return Returns WGPUAdapter.
        */
        WGPUAdapter RequestAdapter();

    private:

        /**
        * @brief Create WGPUInstance.
        */
        void Create();

        /**
        * @brief Create WebGPU Instance Features.
        */
        void GetFeatures();

        /**
        * @brief Create WebGPU Instance Limits.
        */
        void GetLimits();

        /**
        * @brief Is WebGPU Instance has Feature.
        */
        void HasFeature();

        /**
        * @brief Get WebGPU WGSL Features.
        */
        void GetWGSLFeatures();

        /**
        * @brief Is WebGPU WGSL has Feature.
        */
        void HasWGSLFeature();

        /**
        * @brief Process Events.
        */
        void ProcessEvents();

        /**
        * @brief Execute future list and wait for done or timeout.
        */
        void Wait();

        /**
        * @brief Push a future to FutureList.
        * 
        * @param[in] future WGPUFuture.
        */
        void PushToFutureList(const WGPUFuture& future);

    private:

        /**
        * @brief Future waited list.
        */
        std::vector<WGPUFuture> m_FutureList{};

    };

    template<>
    inline void InfrastructureBase::AddRef(Instance* object)
    {
        wgpuInstanceAddRef(object->Handle());
    }
    
    template<>
    inline void InfrastructureBase::Release(Instance* object)
    {
        if (!object->Handle())
        {
            return;
        }

        wgpuInstanceRelease(object->Handle());
        object->SetHandleNullptr();
    }
    
}

#endif