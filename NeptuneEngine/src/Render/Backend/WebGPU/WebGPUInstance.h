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
        * @brief Constructor Function.
        * 
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUInstance(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUInstance() override;

    private:

        /**
        * @brief Create WGPUInstance.
        */
        void CreateInstance();

        /**
        * @brief Create WebGPU Instance Features.
        */
        void GetInstanceFeatures();

        /**
        * @brief Create WebGPU Instance Limits.
        */
        void GetInstanceLimits();

        /**
        * @brief Is WebGPU Instance has Feature.
        */
        void HasInstanceFeature();

        /**
        * @brief Create WebGPU Surface.
        */
        void CreateSurface();

        /**
        * @brief Get WebGPU WGSL Features.
        */
        void GetWGSLLanguageFeatures();

        /**
        * @brief Is WebGPU WGSL has Feature.
        */
        void HasWGSLLanguageFeature();

        /**
        * @brief Process Events.
        */
        void ProcessEvents();

        /**
        * @brief Request WGPUAdapter.
        * 
        * @return Returns WGPUAdapter.
        */
        WGPUAdapter RequestAdapter();

        /**
        * @brief Execute future list and wait for done or timeout.
        */
        void WaitAny();

        /**
        * @brief Add Ref.
        */
        void AddRef();

        /**
        * @brief Release WGPUInstance.
        */
        void Release();

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
        std::vector<WGPUFuture> m_Future{};
    };
}

#endif