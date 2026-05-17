/**
* @file Adapter.h.
* @brief The Adapter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/Adapter.h"

namespace Neptune::WebGPU {

    using IAdapter = IInfrastructure<class Adapter, EInfrastructure::Adapter>;

    /**
    * @brief WebGPU::Adapter Class.
    * This class defines the WebGPU::Adapter behaves.
    */
    class Adapter : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Adapter(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Adapter() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Adapter::Handle& Handle() const { return m_Adapter.GetHandle(); }

    private:

        /**
        * @brief Create Adapter.
        */
        void Create();

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

        Unit::Adapter m_Adapter;  // @brief This Adapter.
    };
    
}

#endif