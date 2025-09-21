/**
* @file EditorWorld.h.
* @brief The EditorWorld Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <World/World/World.h>

namespace Neptune::Editor {

    /**
    * @brief Editor World Class.
    */
    class EditorWorld : public World
    {
    public:

        /**
        * @brief Constructor Function.
        */
        EditorWorld() = default;

        /**
        * @brief Destructor Function.
        */
        ~EditorWorld() override = default;

        /**
        * @brief Interface of World attached to Application.
        */
        void OnAttached() override;

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

        /**
        * @brief Create example scene to world.
        */
        void CreateExampleScene();
        
    };
    
}