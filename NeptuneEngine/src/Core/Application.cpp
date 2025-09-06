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
#include "Window/Window.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

namespace Neptune {

    static UP<Application> S_Instance = nullptr;

    Application& Application::Instance()
    {
        if(!S_Instance)
        {
            S_Instance = CreateUP<Application>();
            NEPTUNE_CORE_INFO("Application created.")
        }

        return *S_Instance;
    }

    void Application::Destroy()
    {
#ifndef NP_PLATFORM_EMSCRIPTEN
        S_Instance.reset();
        S_Instance = nullptr;
#endif
        NEPTUNE_CORE_INFO("Application destroyed.")
    }

    Application::Application()
    {
#ifdef NP_PLATFORM_EMSCRIPTEN
        m_Window = Window::Create(WindowInfo{1920, 1080, "Neptune"}, WindowImplement::emscripten_glfw).get();
#endif

#ifdef NP_PLATFORM_WINDOWS
        m_Window = Window::Create(WindowInfo{ 1920, 1080, "Neptune" }, WindowImplement::GLFW).get();
#endif

        m_SystemManager = CreateUP<SystemManager>();
        m_SystemManager
        ->PushSystem<LogicalSystem>()
        ->PushSystem<RenderSystem>()
        ->PushSystem<RHISystem>();
    }

    Application::~Application()
    {
        m_SystemManager->PopAllSystems();
        Window::Destroy();
    }

    void Application::Run() const
    {
        
#ifdef NP_PLATFORM_EMSCRIPTEN

        // tell emscripten to use "MainLoop" as the main loop
        emscripten_set_main_loop_arg(MainLoop, this, 0, 0);

#else

        while(m_Window->IsWindowActive())
        {
            m_Window->PollEvents();
            m_SystemManager->Run();
        }

#endif

    }

#ifdef NP_PLATFORM_EMSCRIPTEN

    void Application::MainLoop(void* iUserData)
    {
        auto p = reinterpret_cast<Application*>(iUserData);

        if(p->m_Window->IsWindowActive())
        {
            p->m_Window->PollEvents();
            p->m_SystemManager->Run();

            return;
        }

        emscripten_cancel_main_loop();
    }

#endif

}