/**
* @file SystemManager.h.
* @brief The SystemManager Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Library/ClassLibrary.h"
#include "System.h"

namespace Neptune {

    using namespace ClassLibrary;

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
        SystemManager() = default;

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
        void Run();

    private:

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