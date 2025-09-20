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
#include "World/World/World.h"
#include "World/Scene/Scene.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

namespace Neptune {

    static UP<Application> S_Instance = nullptr;

    Application& Application::Instance()
    {
        NEPTUNE_PROFILE_ZONE

        if(!S_Instance)
        {
            S_Instance = CreateUP<Application>();
            NEPTUNE_CORE_INFO("Application created.")
        }

        return *S_Instance;
    }

    void Application::Destroy()
    {
        NEPTUNE_PROFILE_ZONE

#ifndef NP_PLATFORM_EMSCRIPTEN

        S_Instance.reset();
        S_Instance = nullptr;

        NEPTUNE_CORE_INFO("Application destroyed.")
#endif
    }

    Application::Application()
    {
        NEPTUNE_PROFILE_ZONE

#ifdef NP_PLATFORM_EMSCRIPTEN
        m_Window = Window::Create(WindowInfo{1920, 1080, "Neptune"}, WindowImplement::emscripten_glfw, RenderBackendEnum::WebGPU).get();
#endif

#ifdef NP_PLATFORM_WINDOWS
        m_Window = Window::Create(WindowInfo{ 1920, 1080, "Neptune" }, WindowImplement::GLFW, RenderBackendEnum::OpenGL).get();
#endif

        m_SystemManager = CreateUP<SystemManager>();
        m_SystemManager
        ->PushSystem<LogicalSystem>()
        ->PushSystem<RenderSystem>()
        ->PushSystem<RHISystem>();

        m_World = CreateWorld();
    }

    Application::~Application()
    {
        NEPTUNE_PROFILE_ZONE

        m_World.reset();

        m_SystemManager->PopAllSystems();

        Window::Destroy();

        Log::Reset();
    }

    void Application::Run()
    {
        // on attach world to application.
        m_World->OnAttached();
        
#ifdef NP_PLATFORM_EMSCRIPTEN

        // tell emscripten to use "MainLoop" as the main loop
        emscripten_set_main_loop_arg(MainLoop, this, 0, 0);

#else

        while(m_Window->IsWindowActive())
        {
            NEPTUNE_PROFILE_ZONEN("MainLoop")

            m_Window->PollEvents();

            m_SystemManager->Run();

            m_Window->SwapBuffers();

            NEPTUNE_PROFILE_FRAME
        }

        // on detach world to application.
        m_World->OnDetached();
        
#endif

    }

#ifdef NP_PLATFORM_EMSCRIPTEN

    void Application::MainLoop(void* iUserData)
    {
        NEPTUNE_PROFILE_ZONE

        auto p = reinterpret_cast<Application*>(iUserData);

        if(p->m_Window->IsWindowActive())
        {
            p->m_Window->PollEvents();

            p->m_SystemManager->Run();

            p->m_Window->SwapBuffers();

            NEPTUNE_PROFILE_FRAME

            return;
        }

        // on detach world to application.
        p->m_World->OnDetached();
        
        emscripten_cancel_main_loop();
    }

#endif

}