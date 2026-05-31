/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/Device.h"

namespace Neptune::WebGPU {

    using IDevice = IInfrastructure<class Device, EInfrastructure::Device>;

    /**
    * @brief WebGPU::Device Class.
    * This class defines the WebGPU::Device behaves.
    */
    class Device : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Device(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Device() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Device::Handle& Handle() const { return m_Device.GetHandle(); }

    public:

        /**
        * @brief Create Bind Group.
        */
        void CreateBindGroup();

        /**
        * @brief Create Bind Group Layout.
        */
        void CreateBindGroupLayout();

        /**
        * @brief Create Buffer.
        */
        void CreateBuffer();

        /**
        * @brief Create CommandEncoder.
        */
        void CreateCommandEncoder();

        /**
        * @brief Create ComputePipeline.
        */
        void CreateComputePipeline();

        /**
        * @brief Create ComputePipeline Async.
        */
        void CreateComputePipelineAsync();

        /**
        * @brief Create PipelineLayout.
        */
        void CreatePipelineLayout();

        /**
        * @brief Create QuerySet.
        */
        void CreateQuerySet();

        /**
        * @brief Create RenderBundle Encoder.
        */
        void CreateRenderBundleEncoder();

        /**
        * @brief Create Render Pipeline.
        */
        void CreateRenderPipeline();

        /**
        * @brief Create Render Pipeline Async.
        */
        void CreateRenderPipelineAsync();

        /**
        * @brief Create Sampler.
        */
        void CreateSampler();

        /**
        * @brief Create ShaderModule.
        */
        void CreateShaderModule();

        /**
        * @brief Create Texture.
        */
        void CreateTexture();

        /**
        * @brief Destroy Device.
        */
        void Destroy();

        /**
        * @brief Get Adapter Information.
        */
        void GetAdapterInfo();

        /**
        * @brief Get Device Features.
        */
        void GetFeatures();

        /**
        * @brief Get Device Limits.
        */
        void GetLimits();

        /**
        * @brief Get Lost Future.
        */
        void GetLostFuture();

        /**
        * @brief Is Device has Feature.
        */
        void HasFeature();

        /**
        * @brief Pop Error Scope from Device.
        */
        void PopErrorScope();

        /**
        * @brief Push Error Scope to Device.
        */
        void PushErrorScope();
        
    private:

        /**
        * @brief Create Device.
        */
        void Create();

    private:

        Unit::Device m_Device;  // @brief This Device.
    };
    
}

#endif