/**
* @file RenderSystem.h.
* @brief The RenderSystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

namespace Neptune {

    class RenderFrontend;
    
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
        ~RenderSystem() override = default;

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
        
        void Wait() override;
        void OnEvent(Event& event) override;

    private:

        bool OnEngineEvent(class EngineEvent& e);

        bool OnSlateResizeEvent(class SlateResizeEvent& e);

        bool OnWindowResizeOverEvent(class WindowResizeOverEvent& e);

    private:

        /**
        * @brief Render Frontend.
        */
        SP<RenderFrontend> m_RenderFrontend;
    };
}