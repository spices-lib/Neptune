/**
* @file SystemManager.h.
* @brief The SystemManager Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

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

    private:

        /**
        * @brief Push a system to this manager.
        *
        * @tparam T Specific system Class.
        * @param[in] args system params.
        */
        template<typename T, typename ...Args>
        void PushSystem(Args&&... args);

        /**
        * @brief Pop a system from this manager.
        */
        void PopSystem();

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
        std::vector<UP<System>> m_Systems;
    };

    template<typename T, typename ...Args>
    void SystemManager::PushSystem(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        m_Systems.emplace_back(CreateUP<T>(std::forward<Args>(args)...));
        
        m_Systems.back()->OnSystemInitialize();
    }
}