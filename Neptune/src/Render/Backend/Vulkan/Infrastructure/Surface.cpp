/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Surface.h"
#include "Window/Window.h"
#include "Surface/GLFW/Surface.h"

namespace Neptune::Vulkan {

    SP<Surface> Surface::Create(Context& context, EInfrastructure e, WindowImplement implement, void* window)
    {
        NEPTUNE_PROFILE_ZONE

        switch (implement)
        {
            case WindowImplement::GLFW:            return CreateSP<GLFW::Surface>(context, e, window);
            default:
            {
                NEPTUNE_CORE_ERROR("Surface Create with WindowImplement that not supported.")
                return nullptr;
            }
        }
    }

}

#endif