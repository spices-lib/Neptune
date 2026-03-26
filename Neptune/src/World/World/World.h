/**
* @file World.h.
* @brief The World Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "WorldMarkFlag.h"
#include "Core/Container/BitSet.hpp"

#include <unordered_map>

namespace Neptune {

    class Scene;
    class Level;

    namespace Slate {

        class Slate;
    }

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
        virtual void OnAttached();

        /**
        * @brief Interface of World detached to Application.
        */
        virtual void OnDetached();
        
        void OnLayout();

        void OnEvent(Event& e);

        /**
        * @brief Get World activate Scenes.
        * 
        * @return Returns World activate Scenes.
        */
        const std::unordered_map<std::string, UP<Scene>>& GetScenes() const { return m_Scenes; }

        /**
        * @brief Is WorldMark Flag has bit.
        *
        * @param[in] bit In WorldMarkBit.
        * 
        * @return Returns bit value.
        */
        bool TestFlag(WorldMarkBit bit) const { return m_Flag.Test(bit); }

        template<typename T, typename... Args>
        void RegistrySlate(Args&&... args);

    protected:
        
        /**
        * @brief Interface of World UI Layout, as View in MVP.
        */
        virtual void Layout();

        void OnEvent(Event& e);

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
        
        void DestroyScene();

        /**
        * @brief Set WorldMarkBit with value.
        *
        * @param[in] bit WorldMarkBit item.
        * @param[in] value WorldMarkBit value.
        */
        void SetFlag(WorldMarkBit bit, bool value) { m_Flag.Set(bit, value); }

        /**
        * @brief Reset WorldMark Flag to None.
        */
        void ResetFlag() { m_Flag.Reset(); }

    private:
        
        /**
        * @brief World activate Scenes.
        */
        std::unordered_map<std::string, UP<Scene>> m_Scenes;

        /**
        * @brief WorldMark Flag.
        */
        Container::BitSet<WorldMarkBit> m_Flag;
    
        std::vector<SP<Slate::Slate>> m_Slates;
    };

    /**
    * @brief extern WorldCreation definition in Entry.
    *
    * @return Returns World Pointer.
    */
    SP<World> CreateWorld();
    
    template<typename T, typename ...Args>
    inline void World::RegistrySlate(Args && ...args)
    {
        m_Slates.emplace_back(CreateSP<T>(std::forward<Args>(args)...));
    }
}

/**
* @brief extern WorldCreation definition in Entry.
*
* @return Returns World Pointer.
*/
extern Neptune::SP<Neptune::World> Neptune::CreateWorld();