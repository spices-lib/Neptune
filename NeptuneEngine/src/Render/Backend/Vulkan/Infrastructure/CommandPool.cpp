/**
* @file CommandPool.cpp.
* @brief The CommandPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandPool.h"

namespace Neptune::Vulkan {

    CommandPool::CommandPool(Context& context)
        : Infrastructure(context)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void CommandPool::Create()
    {

    }

}

#endif