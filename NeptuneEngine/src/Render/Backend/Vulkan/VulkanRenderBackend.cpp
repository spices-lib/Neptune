/**
* @file VulkanRenderBackend.cpp.
* @brief The VulkanRenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanRenderBackend.h"
#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"

namespace Neptune {

    VulkanRenderBackend::VulkanRenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        m_Context = CreateSP<VulkanContext>();

        m_Context->Registry<VulkanInstance>();
        m_Context->Registry<VulkanSurface>();
        m_Context->Registry<VulkanPhysicalDevice>();
        m_Context->Registry<VulkanDevice>();
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