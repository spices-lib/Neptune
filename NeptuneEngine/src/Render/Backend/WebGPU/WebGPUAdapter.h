/**
* @file WebGPUAdapter.h.
* @brief The WebGPUAdapter Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUObject.h"

namespace Neptune {

    /**
    * @brief WebGPUAdapter Class.
    */
    class WebGPUAdapter : public WebGPUObject
    {
    public:

        /**
        * @brief Mark as WebGPUAdapter Type.
        */
        static constexpr EWebGPUObject Type = EWebGPUObject::WebGPUAdapter;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUAdapter(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        ~WebGPUAdapter() override = default;

        /**
        * @brief Get Row WebGPU Object.
        *
        * @return Returns Row WebGPU Object.
        */
        WGPUAdapter& Row() { return m_Adapter; }

        /**
        * @brief Request WGPUDevice.
        *
        * @return Returns WGPUDevice.
        */
        WGPUDevice RequestDevice();

    public:

        /**
        * @brief Get EWebGPUObject.
        *
        * @return Returns EWebGPUObject.
        */
        const EWebGPUObject& GetType() const override { return WebGPUAdapter::Type; };

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

    private:

        /**
        * @brief WGPUAdapter.
        */
        WGPUAdapter m_Adapter = nullptr;
    };

    template<>
    inline void WebGPUObject::AddRef(WebGPUAdapter* object)
    {
        wgpuAdapterAddRef(object->Row());
    }
    
    template<>
    inline void WebGPUObject::Release(WebGPUAdapter* object)
    {
        if (!object->Row())
        {
            return;
        }

        wgpuAdapterRelease(object->Row());
        object->Row() = nullptr;
    }
    
}

#endif