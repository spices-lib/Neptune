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
        virtual ~SystemManager() override = default;

        /**
		* @brief Push a system to this manager.
		* @tparam T Specific system Class.
		* @return Returns the SystemManager.
		*/
        template<typename T, typename ...Args>
        SystemManager* PushSystem(Args&&... args);

        /**
		* @brief Pop a system from this manager.
		* @return Returns the SystemManager.
		*/
        SystemManager* PopSystem();

        /**
		* @brief Pop all system from this manager.
		*/
        void PopAllSystems();

        /**
		* @brief Update all system that pushed to this manager.
		*/
        void Run() const;

    private:

        /**
		* @brief The root event function pointer.
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
    inline SystemManager* SystemManager::PushSystem(Args&&... args)
    {
        m_Systems.emplace_back(CreateUP<T>(std::forward<Args>(args)...));
        m_Systems.back()->OnSystemInitialize();

        return this;
    }
}