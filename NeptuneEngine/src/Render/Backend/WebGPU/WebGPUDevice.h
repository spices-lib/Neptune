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

        void CreateBindGroup();
        void CreateBindGroupLayout();
        void CreateBuffer();
        void CreateCommandEncoder();
        void CreateComputePipeline();
        void CreateComputePipelineAsync();
        void CreatePipelineLayout();
        void CreateQuerySet();
        void CreateRenderBundleEncoder();
        void CreateRenderPipeline();
        void CreateRenderPipelineAsync();
        void CreateSampler();
        void CreateShaderModule();
        void CreateTexture();
        void Destroy();
        void GetAdapterInfo();
        void GetFeatures();
        void GetLimits();
        void GetLostFuture();
        WGPUQueue GetQueue();
        void HasFeature();
        void PopErrorScope();
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