/**
* @file EditorWorld.h.
* @brief The EditorWorld Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <World/World/World.h>

namespace Neptune {
    
    class EditorWorld : public World
    {
    public:

        EditorWorld() = default;
        ~EditorWorld() override = default;
        
        void Layout() override {}
    
    };
    
}