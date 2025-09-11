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
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPUContext.
        */
        WebGPUAdapter(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUAdapter() override = default;


    private:

        void GetFeatures();
        void GetInfo();
        void GetLimits();
        void HasFeature();
        void RequestDevice();
        void AddRef();
        void Release();

    private:

        /**
        * @brief WGPUAdapter.
        */
        WGPUAdapter m_Adapter = nullptr;

    };
}

#endif