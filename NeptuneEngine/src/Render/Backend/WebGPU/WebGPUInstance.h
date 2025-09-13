/**
* @file WebGPUInstance.h.
* @brief The WebGPUInstance Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUObject.h"

namespace Neptune {

    /**
    * @brief WebGPUInstance Class.
    */
    class WebGPUInstance : public WebGPUObject
    {
    public:

        /**
        * @brief Mark as WebGPUInstance Type.
        */
        static constexpr EWebGPUObject Type = EWebGPUObject::WebGPUInstance;
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUInstance(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        ~WebGPUInstance() override = default;

        /**
        * @brief Get Row WebGPU Object.
        *
        * @return Returns Row WebGPU Object.
        */
        WGPUInstance& Row() { return m_Instance; }

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

    public:

        /**
        * @brief Get EWebGPUObject.
        *
        * @return Returns EWebGPUObject.
        */
        const EWebGPUObject& GetType() const override { return WebGPUInstance::Type; };

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
        * @brief WGPUInstance.
        */
        WGPUInstance m_Instance = nullptr;

        /**
        * @brief Future waited list.
        */
        std::vector<WGPUFuture> m_FutureList{};

    };

    template<>
    inline void WebGPUObject::AddRef(WebGPUInstance* object)
    {
        wgpuInstanceAddRef(object->Row());
    }
    
    template<>
    inline void WebGPUObject::Release(WebGPUInstance* object)
    {
        if (!object->Row())
        {
            return;
        }

        wgpuInstanceRelease(object->Row());
        object->Row() = nullptr;
    }
    
}

#endif