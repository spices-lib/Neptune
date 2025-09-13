/**
* @file WebGPUDevice.h.
* @brief The WebGPUDevice Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUObject.h"

namespace Neptune {

    /**
    * @brief WebGPUDevice Class.
    */
    class WebGPUDevice : public WebGPUObject
    {
    public:
        
        /**
        * @brief Mark as WebGPUDevice Type.
        */
        static constexpr EWebGPUObject Type = EWebGPUObject::WebGPUDevice;
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUDevice(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        ~WebGPUDevice() override = default;

        /**
        * @brief Get Row WebGPU Object.
        * 
        * @return Returns Row WebGPU Object.
        */
        WGPUDevice& Row() { return m_Device; }
    
    public:

        /**
        * @brief Get EWebGPUObject.
        *
        * @return Returns EWebGPUObject.
        */
        const EWebGPUObject& GetType() const override { return WebGPUDevice::Type; };

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

    private:

        /**
        * @brief WGPUDevice.
        */
        WGPUDevice m_Device = nullptr;
        
    };

    template<>
    inline void WebGPUObject::AddRef(WebGPUDevice* object)
    {
        wgpuDeviceAddRef(object->Row());
    }
    
    template<>
    inline void WebGPUObject::Release(WebGPUDevice* object)
    {
        if (!object->Row())
        {
            return;
        }

        wgpuDeviceRelease(object->Row());
        object->Row() = nullptr;
    }

    template<>
    inline void WebGPUObject::SetLabel(WebGPUDevice* object, const std::string& label)
    {
        WGPUStringView view{ label.c_str() };

        wgpuDeviceSetLabel(object->Row(), view);
    }
    
}

#endif