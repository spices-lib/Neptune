/**
* @file RenderSystem.h.
* @brief The RenderSystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

namespace Neptune {

    /**
    * @brief RenderSystem Class.
    * This class defines the RenderSystem behaves.
    */
    class RenderSystem : public System
    {
    public:

        /**
        * @brief Constructor Function.
        */
        RenderSystem() : System() {}

        /**
        * @brief Destructor Function.
        */
        virtual ~RenderSystem() override = default;

        /**
        * @brief Interface of system initialize.
        */
        virtual void OnSystemInitialize() override {}

        /**
        * @brief Interface of system shutdown.
        */
        virtual void OnSystemShutDown() override {}

        /**
        * @brief Interface of system tick run.
        */
        virtual void Tick() override {}
    };
}