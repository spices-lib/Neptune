/**
* @file Application.cpp.
* @brief The Application Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Application.h"
#include "Systems/SystemManager.h"
#include "Systems/LogicalSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/RHISystem.h"
#include "World/Document/DocumentContext.h"
#include "Window/Window.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

namespace Neptune {

    static UP<Application> S_Instance = nullptr;

    Application& Application::Instance()
    {
        if(!S_Instance)
        {
            S_Instance = CreateUP<Application>();
        }

        return *S_Instance;
    }

    void Application::Destroy()
    {
#ifndef __EMSCRIPTEN__
        S_Instance.reset();
        S_Instance = nullptr;
#endif
    }

    Application::Application()
    {
        m_Window = Window::Create(WindowInfo{1920, 1080, "Neptune"}, WindowImplement::emscripten_glfw).get();

        m_SystemManager = CreateUP<SystemManager>();
        m_SystemManager
        ->PushSystem<LogicalSystem>()
        ->PushSystem<RenderSystem>()
        ->PushSystem<RHISystem>();

        m_DocumentContext = CreateUP<DocumentContext>();
    }

    Application::~Application()
    {
        m_DocumentContext.reset();
        m_SystemManager->PopAllSystems();
        Window::Destroy();
    }

    void Application::Run()
    {
        // Specify the current Document, which created from Entry.
        m_DocumentContext->m_Document = CreateDocument();

        // Document preLoad.
        m_DocumentContext->m_Page->OnPreLoad(m_DocumentContext->m_Document.get());

#ifdef __EMSCRIPTEN__

        // tell emscripten to use "MainLoop" as the main loop
        emscripten_set_main_loop_arg(MainLoop, this, 0, 0);

#else

        while(m_Window->IsWindowActive())
        {
            m_Window->PollEvents();
            m_SystemManager->Run();
        }

        m_DocumentContext->m_Page->OnDeactivate();

#endif

    }

    void Application::MainLoop(void* iUserData)
    {
        auto p = reinterpret_cast<Application*>(iUserData);

        if(p->m_Window->IsWindowActive())
        {
            p->m_Window->PollEvents();
            p->m_SystemManager->Run();

            return;
        }

        p->m_DocumentContext->m_Page->OnDeactivate();
        emscripten_cancel_main_loop();
    }

}