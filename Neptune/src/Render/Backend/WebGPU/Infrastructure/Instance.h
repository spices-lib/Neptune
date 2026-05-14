/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/Instance.h"

namespace Neptune::WebGPU {

    using IInstance = IInfrastructure<class Instance, EInfrastructure::Instance>;

    /**
    * @brief WebGPU::Instance Class.
    * This class defines the WebGPU::Instance behaves.
    */
    class Instance : public Infrastructure
    { 
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Instance(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Instance() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Instance::Handle& Handle() const { return m_Instance.GetHandle(); }

    private:

        /**
        * @brief Create WebGPU Surface.
        *
        * @param[in] htmlCanvas HTML Canvas id.
        *
        * @return Returns WGPUSurface.
        */
        WGPUSurface CreateSurface(const std::string& htmlCanvas);

        /**
        * @brief Create Instance.
        */
        void Create();

        /**
        * @brief Create Instance Features.
        */
        void GetFeatures();

        /**
        * @brief Create Instance Limits.
        */
        void GetLimits();

        /**
        * @brief Is Instance has Feature.
        */
        void HasFeature();

        /**
        * @brief Get WGSL Features.
        */
        void GetWGSLFeatures();

        /**
        * @brief Is WGSL has Feature.
        */
        void HasWGSLFeature();

        /**
        * @brief Process Events.
        */
        void ProcessEvents();

    private:

        Unit::Instance m_Instance;                                             // @brief This Instance.

    };
    
}

#endif