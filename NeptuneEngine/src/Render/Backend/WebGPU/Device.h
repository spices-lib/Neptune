/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::WebGPU {

    /**
    * @brief Device Class.
    */
    class Device : public Infrastructure<WGPUDevice, EInfrastructure::Device>
    {
    public:
        
        /**
        * @brief Mark as Device Infrastructure Type.
        */
        static constexpr EInfrastructure Type = Infrastructure<WGPUDevice, EInfrastructure::Device>::Type;
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] context The global WebGPU Context.
        */
        explicit Device(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~Device() override = default;

    public:

        /**
        * @brief Create WebGPU Bind Group.
        */
        void CreateBindGroup();

        /**
        * @brief Create WebGPU Bind Group Layout.
        */
        void CreateBindGroupLayout();

        /**
        * @brief Create WebGPU Buffer.
        */
        void CreateBuffer();

        /**
        * @brief Create WebGPU CommandEncoder.
        */
        void CreateCommandEncoder();

        /**
        * @brief Create WebGPU ComputePipeline.
        */
        void CreateComputePipeline();

        /**
        * @brief Create WebGPU ComputePipeline Async.
        */
        void CreateComputePipelineAsync();

        /**
        * @brief Create WebGPU PipelineLayout.
        */
        void CreatePipelineLayout();

        /**
        * @brief Create WebGPU QuerySet.
        */
        void CreateQuerySet();

        /**
        * @brief Create WebGPU RenderBundle Encoder.
        */
        void CreateRenderBundleEncoder();

        /**
        * @brief Create WebGPU Render Pipeline.
        */
        void CreateRenderPipeline();

        /**
        * @brief Create WebGPU Render Pipeline Async.
        */
        void CreateRenderPipelineAsync();

        /**
        * @brief Create WebGPU Sampler.
        */
        void CreateSampler();

        /**
        * @brief Create WebGPU ShaderModule.
        */
        void CreateShaderModule();

        /**
        * @brief Create WebGPU Texture.
        */
        void CreateTexture();

        /**
        * @brief Destroy WebGPU Device.
        */
        void Destroy();

        /**
        * @brief Get WebGPU Adapter Information.
        */
        void GetAdapterInfo();

        /**
        * @brief Get WebGPU Device Features.
        */
        void GetFeatures();

        /**
        * @brief Get WebGPU Device Limits.
        */
        void GetLimits();

        /**
        * @brief Get WebGPU Lost Future.
        */
        void GetLostFuture();

        /**
        * @brief Get WebGPU Queue.
        * 
        * @return Returns WebGPU Queue.
        */
        WGPUQueue GetQueue();

        /**
        * @brief Is WebGPU Device has Feature.
        */
        void HasFeature();

        /**
        * @brief Pop Error Scope from WebGPU Device.
        */
        void PopErrorScope();

        /**
        * @brief Push Error Scope to WebGPU Device.
        */
        void PushErrorScope();
        
    };

    template<>
    inline void InfrastructureBase::AddRef(Device* object)
    {
        NEPTUNE_PROFILE_ZONE

        wgpuDeviceAddRef(object->Handle());
    }
    
    template<>
    inline void InfrastructureBase::Release(Device* object)
    {
        NEPTUNE_PROFILE_ZONE

        if (!object->Handle())
        {
            return;
        }

        wgpuDeviceRelease(object->Handle());
        object->SetHandleNullptr();
    }

    template<>
    inline void InfrastructureBase::SetLabel(Device* object, const std::string& label)
    {
        NEPTUNE_PROFILE_ZONE

        WGPUStringView view{ label.c_str() };

        wgpuDeviceSetLabel(object->Handle(), view);
    }
    
}

#endif