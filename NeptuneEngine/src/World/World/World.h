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
    class Level;

    /**
    * @brief World Class
    * In program, all elements we see is a world.
    */
    class World : public NonCopyable
    {
    public:

        /**
        * @brief Get World Instance.
        *
        * @return Returns World Instance.
        */
        static SP<World> Instance();

    public:

        /**
        * @brief Constructor Function.
        */
        World() = default;

        /**
        * @brief Destructor Function.
        */
        ~World() override = default;

        /**
        * @brief Interface of World attached to Application.
        */
        virtual void OnAttached() = 0;

        /**
        * @brief Interface of World detached to Application.
        */
        virtual void OnDetached() = 0;
        
        /**
        * @brief Get World activate Scenes.
        * 
        * @return Returns World activate Scenes.
        */
        const std::unordered_map<std::string, UP<Scene>>& GetScenes() const { return m_Scenes; }

    protected:
        
        /**
        * @brief Interface of World UI Layout, as View in MVP.
        */
        virtual void Layout() = 0;

        /**
        * @brief Create Scene with a level to World.
        * Used for deserialize level asset.
        *
        * @param[in] level Level
        *
        * @return Returns scene pointer.
        */
        Scene* CreateScene(const SP<Level>& level);

        /**
        * @brief Create empty Scene with a name to World.
        * Used for object view.
        *
        * @param[in] name Scene name.
        *
        * @return Returns scene pointer.
        */
        Scene* CreateScene(const std::string& name);
        
    private:
        
        /**
        * @brief World activate Scenes.
        */
        std::unordered_map<std::string, UP<Scene>> m_Scenes;
    
    };

    /**
    * @brief extern WorldCreation definition in Entry.
    *
    * @return Returns World Pointer.
    */
    SP<World> CreateWorld();
    
}

/**
* @brief extern WorldCreation definition in Entry.
*
* @return Returns World Pointer.
*/
extern Neptune::SP<Neptune::World> Neptune::CreateWorld();