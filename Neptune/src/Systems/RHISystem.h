/**
* @file RHISystem.h.
* @brief The RHISystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

namespace Neptune {

    class RenderFrontend;

    /**
    * @brief RHISystem Class.
    * This class defines the RHISystem behaves.
    */
    class RHISystem : public System
    {
    public:

        /**
        * @brief Constructor Function.
        */
        RHISystem() : System() {}

        /**
        * @brief Destructor Function.
        */
        ~RHISystem() override = default;

        /**
        * @brief Interface of system initialize.
        */
        void OnSystemInitialize() override;

        /**
        * @brief Interface of system shutdown.
        */
        void OnSystemShutDown() override;

        /**
        * @brief Interface of system tick run.
        */
        void Tick() override;

    private:

        /**
        * @brief Render Frontend.
        */
        SP<RenderFrontend> m_RenderFrontend;
    };
}