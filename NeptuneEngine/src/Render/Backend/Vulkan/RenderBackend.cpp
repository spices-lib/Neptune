/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderBackend.h"
#include "Infrastructure/Instance.h"
#include "Infrastructure/KHR/Surface.h"
#include "Infrastructure/PhysicalDevice.h"
#include "Infrastructure/Device.h"
#include "Infrastructure/MemoryAllocator.h"
#include "Infrastructure/ThreadQueue.h"
#include "Infrastructure/KHR/SwapChain.h"

namespace Neptune::Vulkan {

    RenderBackend::RenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        m_Context = CreateSP<Context>();

        m_Context->Registry<Instance>();
        m_Context->Registry<Surface>();
        m_Context->Registry<PhysicalDevice>();
        m_Context->Registry<Device>();
        m_Context->Registry<ThreadQueue>();
        m_Context->Registry<MemoryAllocator>();
        m_Context->Registry<SwapChain>();
    }

    RenderBackend::~RenderBackend()
    {

    }

    void RenderBackend::BeginFrame()
    {

    }

    void RenderBackend::EndFrame()
    {

    }

    void RenderBackend::RenderFrame()
    {

    }
}

#endif