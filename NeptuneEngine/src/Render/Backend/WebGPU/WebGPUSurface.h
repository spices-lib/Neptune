/**
* @file WebGPUSurface.h.
* @brief The WebGPUSurface Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUObject.h"

namespace Neptune {

    /**
    * @brief WebGPUSurface Class.
    */
    class WebGPUSurface : public WebGPUObject
    {
    public:

        /**
        * @brief Mark as WebGPUSurface Type.
        */
        static constexpr EWebGPUObject Type = EWebGPUObject::WebGPUSurface;

    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUSurface(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        ~WebGPUSurface() override = default;

        /**
        * @brief Get Row WebGPU Object.
        *
        * @return Returns Row WebGPU Object.
        */
        WGPUSurface& Row() { return m_Surface; }

    public:

        /**
        * @brief Get EWebGPUObject.
        *
        * @return Returns EWebGPUObject.
        */
        const EWebGPUObject& GetType() const override { return WebGPUSurface::Type; };

    private:

        void Configure();
        void GetCapabilities();
        void GetCurrentTexture();
        void Present();
        void Unconfigure();

    private:

        /**
        * @brief WebGPUSurface.
        */
        WGPUSurface m_Surface = nullptr;
    };

    template<>
    inline void WebGPUObject::AddRef(WebGPUSurface* object)
    {
        wgpuSurfaceAddRef(object->Row());
    }

    template<>
    inline void WebGPUObject::Release(WebGPUSurface* object)
    {
        if (!object->Row())
        {
            return;
        }

        wgpuSurfaceRelease(object->Row());
        object->Row() = nullptr;
    }

    template<>
    inline void WebGPUObject::SetLabel(WebGPUSurface* object, const std::string& label)
    {
        WGPUStringView view{ label.c_str() };

        wgpuSurfaceSetLabel(object->Row(), view);
    }

}

#endif