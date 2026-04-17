/**
* @file SystemManager.h.
* @brief The SystemManager Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

#include <array>

namespace Neptune {

    class Event;

    /**
    * @brief System Class.
    * This class defines the System behaves.
    */
    class SystemManager : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        SystemManager();

        /**
        * @brief Destructor Function.
        */
    	~SystemManager() override = default;

        /**
        * @brief Initialize Systems.
        */
        void Initialize();

        /**
        * @brief Shutdown Systems.
        */
        void Shutdown();

        /**
		* @brief Update all system that pushed to this manager.
		*/
        void Run() const;

        /**
        * @brief Get SystemManager System.
        *
        * @param[in] system ESystem.
        *
        * @return Returns System Pointer.
        */
        System* GetSystem(ESystem system) const;

    private:

        /**
        * @brief Push a system to this manager.
        *
        * @tparam T Specific system Class.
        * @param[in] system ESystem.
        * @param[in] args system params.
        */
        template<typename T, typename ...Args>
        void PushSystem(ESystem system, Args&&... args);

        /**
		* @brief The root event function pointer.
		* 
		* @param[in] event Event.
		*/
        void OnEvent(Event& event) const;

    private:

        /**
        * @brief Systems queue.
        */
        std::array<UP<System>, static_cast<uint8_t>(ESystem::Count)> m_Systems;
    };

    template<typename T, typename ...Args>
    void SystemManager::PushSystem(ESystem system, Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        auto position = static_cast<uint8_t>(system);

        m_Systems[position] = CreateUP<T>(std::forward<Args>(args)...);
        
        m_Systems[position]->OnSystemInitialize();
    }
}