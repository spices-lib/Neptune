/**
* @file Application.h.
* @brief The Application Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "NonCopyable.h"

namespace Neptune {

    class SystemManager;
    class Window;
    class World;

    /**
    * @brief Application Class.
    * This class defines the Application behaves.
    */
    class Application : public NonCopyable
    {
    public:
        
        /**
         * @brief Get this instance.
         * 
         * @return Returns this instance.
         */
        static Application& Instance();

        /**
         * @brief Destroy this instance.
         */
        static void Destroy();

    public:

        /**
        * @brief Constructor Function.
        */
        Application();

        /**
        * @brief Destructor Function.
        */
        ~Application() override;

        /**
        * @brief MainLoop entry.
        */
        void Run();

    private:

#ifdef NP_PLATFORM_EMSCRIPTEN

        /**
        * @brief MainLoop provided for emscripten.
        *
        * @param[in] iUserData this pointer.
        */
        static void MainLoop(void* iUserData);

#endif

    public:

        UP<SystemManager> m_SystemManager;        // @brief SystemManager
        Window* m_Window;                         // @brief Window
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