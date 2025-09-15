/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::WebGPU {

    /**
    * @brief Surface Class.
    */
    class Surface : public Infrastructure<WGPUSurface, EInfrastructure::Surface>
    {
    public:

        /**
        * @brief Mark as Surface Infrastructure Type.
        */
        static constexpr EInfrastructure Type = Infrastructure<WGPUSurface, EInfrastructure::Surface>::Type;

    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPU Context.
        */
        explicit Surface(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~Surface() override = default;

    private:

        void Configure();
        void GetCapabilities();
        void GetCurrentTexture();
        void Present();
        void Unconfigure();

    };

    template<>
    inline void InfrastructureBase::AddRef(Surface* object)
    {
        wgpuSurfaceAddRef(object->Handle());
    }

    template<>
    inline void InfrastructureBase::Release(Surface* object)
    {
        if (!object->Handle())
        {
            return;
        }

        wgpuSurfaceRelease(object->Handle());
        object->SetHandleNullptr();
    }

    template<>
    inline void InfrastructureBase::SetLabel(Surface* object, const std::string& label)
    {
        WGPUStringView view{ label.c_str() };

        wgpuSurfaceSetLabel(object->Handle(), view);
    }

}

#endif