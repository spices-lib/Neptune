/**
* @file VulkanRenderBackend.cpp.
* @brief The VulkanRenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanRenderBackend.h"


namespace Neptune {

    VulkanRenderBackend::VulkanRenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        
    }

    VulkanRenderBackend::~VulkanRenderBackend()
    {

    }

    void VulkanRenderBackend::BeginFrame()
    {

    }

    void VulkanRenderBackend::EndFrame()
    {

    }

    void VulkanRenderBackend::RenderFrame()
    {

    }
}

#endif