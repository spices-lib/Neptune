/**
* @file VulkanRenderBackend.cpp.
* @brief The VulkanRenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanRenderBackend.h"
#include "Infrastructure/VulkanInstance.h"
#include "Infrastructure/VulkanSurface.h"
#include "Infrastructure/VulkanPhysicalDevice.h"
#include "Infrastructure/VulkanDevice.h"

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