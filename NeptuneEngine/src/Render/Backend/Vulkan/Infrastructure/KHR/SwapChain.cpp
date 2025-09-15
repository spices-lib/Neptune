/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "SwapChain.h"

namespace Neptune::Vulkan {

    SwapChain::SwapChain(Context& context)
        : Infrastructure(context)
    {
        Create();
    }

    void SwapChain::Create()
    {

    }

}

#endif