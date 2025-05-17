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
    class Document;
    class DocumentContext;
    class Window;

    /**
    * @brief Application Class.
    * This class defines the Application behaves.
    */
    class Application : public NonCopyable
    {
    public:

        static UP<Application> Create();

    public:

        /**
        * @brief Constructor Function.
        */
        Application();

        /**
        * @brief Destructor Function.
        */
        virtual ~Application() override;

        void Run();

    private:

        static void MainLoop(void* iUserData);

    private:

        UP<SystemManager> m_SystemManager;
        UP<DocumentContext> m_DocumentContext;
        SP<Window> m_Window;
    };

    /**
	* @brief extern DocumentCreation definition in Entry.
	*/
    SP<Document> CreateDocument();
}

/**
* @brief extern DocumentCreation definition in Entry.
* @return Returns Document Pointer.
*/
extern Neptune::SP<Neptune::Document> Neptune::CreateDocument();