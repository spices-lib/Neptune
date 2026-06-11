/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "SwapChain.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Neptune::Direct3D11::GLFW {

    SwapChain::SwapChain(Context& context, EInfrastructure e, uint32_t count, void* window)
        : Direct3D11::SwapChain(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create(count, window);
    }

	void SwapChain::Create(uint32_t count, void* window)
    {
        NEPTUNE_PROFILE_ZONE

        auto glfwWindow = static_cast<GLFWwindow*>(window);

        int w, h;

        glfwGetWindowSize(glfwWindow, &w, &h);

		DXGI_SWAP_CHAIN_DESC1                desc{};
        desc.Width                         = w;
        desc.Height                        = h;
        
        Direct3D11::SwapChain::Create(desc, count, glfwGetWin32Window(glfwWindow));
    }

}

#endif