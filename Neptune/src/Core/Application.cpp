/**
* @file Application.cpp.
* @brief The Application Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Application.h"
#include "Systems/SystemManager.h"
#include "Window/Window.h"
#include "World/World/World.h"
#include "World/Scene/Scene.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

namespace Neptune {

    namespace {
        
        UP<Application> S_Instance = nullptr;
    }
    
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

        NEPTUNE_CORE_INFO("Application destroyed.")
#endif
    }

    Application::Application()
    {
        NEPTUNE_PROFILE_ZONE

#ifdef NP_PLATFORM_EMSCRIPTEN
        Window::Create(WindowInfo{1920, 1080, "Neptune"}, WindowImplement::emscripten_glfw, RenderBackendEnum::WebGPU);
#endif

#ifdef NP_PLATFORM_WINDOWS
        Window::Create(WindowInfo{ 1920, 1080, "Neptune" }, WindowImplement::GLFW, RenderBackendEnum::Vulkan);
#endif

        m_SystemManager = CreateUP<SystemManager>();
        m_SystemManager->Initialize();
    }

    Application::~Application()
    {
        NEPTUNE_PROFILE_ZONE

        m_SystemManager->Shutdown();

        Window::Destroy();

        Log::Reset();
    }

    void Application::Run()
    {
        // on attach world to application.
        auto& world = World::Instance();

        world.OnAttached();
        
#ifdef NP_PLATFORM_EMSCRIPTEN

        // tell emscripten to use "MainLoop" as the main loop
        emscripten_set_main_loop_arg(MainLoop, this, 0, 0);

#else

        const auto& window = Window::Instance();

        while(window.IsWindowActive())
        {
            NEPTUNE_PROFILE_ZONEN("MainLoop")

            window.PollEvents();

            m_SystemManager->Run();

            NEPTUNE_PROFILE_FRAME
        }

        // on detach world to application.
        world.OnDetached();
        
#endif

    }

#ifdef NP_PLATFORM_EMSCRIPTEN

    void Application::MainLoop(void* iUserData)
    {
        NEPTUNE_PROFILE_ZONE

        auto p = reinterpret_cast<Application*>(iUserData);

        const auto& window = Window::Instance();

        if(window.IsWindowActive())
        {
            window.PollEvents();

            p->m_SystemManager->Run();

            NEPTUNE_PROFILE_FRAME

            return;
        }

        // on detach world to application.
        auto& world = World::Instance();

        world.OnDetached();
        
        emscripten_cancel_main_loop();
    }

#endif

}