/**
* @file RuntimeWorld.h.
* @brief The RuntimeWorld Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <World/World/World.h>

namespace Neptune::Runtime {

    /**
    * @brief Editor World Class.
    */
    class RuntimeWorld : public World
    {
    public:

        /**
        * @brief Constructor Function.
        */
        RuntimeWorld() = default;

        /**
        * @brief Destructor Function.
        */
        ~RuntimeWorld() override = default;

        /**
        * @brief Interface of World attached to Application.
        */
        void OnAttached() override {}

        /**
        * @brief Interface of World detached to Application.
        */
        void OnDetached() override {}
        
    protected:
        
        /**
        * @brief Interface of World UI Layout, as View in MVP.
        * Create Editor Layout here.
        */
        void Layout() override;

    private:
        
    };
    
}