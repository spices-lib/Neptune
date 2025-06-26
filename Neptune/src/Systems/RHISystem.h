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
        virtual ~RHISystem() override = default;

        /**
        * @brief Interface of system initialize.
        */
        virtual void OnSystemInitialize() override;

        /**
        * @brief Interface of system shutdown.
        */
        virtual void OnSystemShutDown() override;

        /**
        * @brief Interface of system tick run.
        */
        virtual void Tick() override;

    private:

        /**
        * @brief Render Frontend.
        */
        SP<RenderFrontend> m_RenderFrontend;
    };
}