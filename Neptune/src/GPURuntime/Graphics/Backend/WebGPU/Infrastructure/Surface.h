/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/Surface.h"

namespace Neptune::WebGPU {

    using ISurface = IInfrastructure<class Surface, EInfrastructure::Surface>;

    /**
    * @brief WebGPU::Surface Class.
    * This class defines the WebGPU::Surface behaves.
    */
    class Surface : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Surface(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Surface() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Surface::Handle& Handle() const { return m_Surface.GetHandle(); }

    private:

        /**
        * @brief Create Surface.
        */
        void Create();

        void Configure() const;
        void GetCapabilities() const;
        void GetCurrentTexture() const;
        void Present() const;
        void Unconfigure() const;

    private:

        Unit::Surface m_Surface;  // @brief This Surface.
    };

}

#endif