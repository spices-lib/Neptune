/**
* @file Adapter.h.
* @brief The Adapter Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::WebGPU {

    /**
    * @brief Adapter Class.
    */
    class Adapter : public Infrastructure<WGPUAdapter, EInfrastructure::Adapter>
    {
    public:

        /**
        * @brief Mark as Adapter Infrastructure Type.
        */
        static constexpr EInfrastructure Type = Infrastructure<WGPUAdapter, EInfrastructure::Adapter>::Type;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPU Context.
        */
        explicit Adapter(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~Adapter() override = default;

        /**
        * @brief Request WGPUDevice.
        *
        * @return Returns WGPUDevice.
        */
        WGPUDevice RequestDevice();

    private:

        /**
        * @brief Get WebGPU Adapter Features.
        */
        void GetFeatures();

        /**
        * @brief Get WebGPU Adapter Info.
        */
        void GetInfo();

        /**
        * @brief Get WebGPU Adapter Limits.
        */
        void GetLimits();

        /**
        * @brief Is WebGPU Adapter has Features.
        */
        void HasFeature();

    };

    template<>
    inline void InfrastructureBase::AddRef(Adapter* object)
    {
        wgpuAdapterAddRef(object->Handle());
    }
    
    template<>
    inline void InfrastructureBase::Release(Adapter* object)
    {
        if (!object->Handle())
        {
            return;
        }

        wgpuAdapterRelease(object->Handle());
        object->SetHandleNullptr();
    }
    
}

#endif