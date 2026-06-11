/**
* @file WindowContext.cpp.
* @brief The WindowContext Class Implementation.
* @author Spices.
*/
#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "WindowContext.h"
#include "WindowContext/GLFW/WindowContext.h"

namespace Neptune::OpenGL {

	SP<WindowContext> WindowContext::Create(Context& context, EInfrastructure e, WindowImplement implement, void* window)
	{
        NEPTUNE_PROFILE_ZONE

        switch (implement)
        {
            case WindowImplement::GLFW: return CreateSP<GLFW::WindowContext>(context, e, window);
            default:
            {
                NEPTUNE_CORE_ERROR("WindowContext Create with WindowImplement that not supported.")
                return nullptr;
            }
        }
	}
}

#endif