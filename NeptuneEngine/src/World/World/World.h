/**
* @file World.h.
* @brief The World Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <unordered_map>

namespace Neptune {

    class Scene;
    
    class World : public NonCopyable
    {
    public:

        World() = default;
        ~World() override = default;

        virtual void Layout() = 0;
        
    private:
        
        /**
         * @brief World activate Scenes.
         */
        std::unordered_map<std::string, SP<Scene>> m_Scenes;
    
    };
    
}