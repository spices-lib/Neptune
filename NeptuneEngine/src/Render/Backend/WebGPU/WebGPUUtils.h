/**
* @file WebGPUUtils.h.
* @brief The WebGPUObject Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"

#include <webgpu.h>

#include <vector>

namespace Neptune {

/**
* @brief Max In Flight Frame.
* 2 buffers are enough in this program.
*/
constexpr uint32_t MaxFrameInFlight = 2;

	/**
	* @brief Handle WebGPUStatus Function.
	* @param[in] result WebGPUStatus.
	*/
	static void HandleWebGPUResult(WGPUStatus result)
	{
		if (result == WGPUStatus::WGPUStatus_Success) return;

        NEPTUNE_CORE_ERROR("Render backend throw error.")
	}

	/**
	* @brief WebGPU Check macro.
	* Verify WebGPU API Effectiveness.
	*/
	#define WEBGPU_CHECK(expr)  { auto expr_value = expr;  ASSERT(expr_value == WGPUStatus::WGPUStatus_Success);  HandleWebGPUResult(expr_value); }

    /**
    * @brief This struct contains all WebGPU object in used global.
    */
    class WebGPUState : NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        WebGPUState() = default;

        WGPUInstance                                       m_Instance;                   /* @brief From WebGPUInstance.                                            */
        WGPUSurface                                        m_Surface;                    /* @brief From WebGPUInstance.                                            */
        //WGPUPhysicalDevice                                 m_PhysicalDevice;             /* @brief From WebGPUDevice.                                              */
        WGPUDevice                                         m_Device;                     /* @brief From WebGPUDevice.                                              */
        //VmaAllocator                                     m_VmaAllocator;               /* @brief From WebGPUMemoryAllocator.                                     */
        //VulkanFunctions                                  m_VkFunc;                     /* @brief From WebGPUFunctions.                                           */
        WGPUQueue									       m_GraphicQueue;               /* @brief From WebGPUDevice, Queue for graphic compute.                   */
        //uint32_t                                           m_GraphicQueueFamily;         /* @brief From WebGPUDevice, ID for graphic queue.                        */
        //WGPUQueue									       m_PresentQueue;               /* @brief From WebGPUDevice, Queue for present windows.                   */
        //WGPUQueue										   m_TransferQueue;              /* @brief From WebGPUDevice, Queue for transfer buffer.                   */
        //WGPUQueue								  	       m_ComputeQueue;               /* @brief From WebGPUDevice, Queue for compute shader.                    */
        //uint32_t                                           m_ComputeQueueFamily;         /* @brief From WebGPUDevice, ID for compute queue.                        */
        std::array<WGPUTexture,           MaxFrameInFlight>  m_SwapChainImages;            /* @brief The SwapChain's image, used for present.                        */
        std::array<WGPUTextureView,       MaxFrameInFlight>  m_SwapChainImageViews;        /* @brief The SwapChain's imageView.                                      */
        std::array<WGPUSampler,         MaxFrameInFlight>  m_SwapChainImageSamplers;     /* @brief The SwapChain's imageSampler.                                   */

        // Used for Graphic Queue
        //WGPUCommandPool                                    m_GraphicCommandPool;         /* @brief From WebGPUCommandBuffer                                        */
        WGPUCommandEncoder  m_GraphicCommandEncoder;                                       /* @brief From WebGPUCommandBuffer, Array num equals to MaxFrameInFlight. */
        //std::array<WGPUSemaphore,       MaxFrameInFlight>  m_GraphicImageSemaphore;      /* @brief From WebGPUSwapChain, Array num equals to MaxFrameInFlight.     */
        //std::array<WGPUSemaphore,       MaxFrameInFlight>  m_GraphicQueueSemaphore;      /* @brief From WebGPUSwapChain, Array num equals to MaxFrameInFlight.     */
        //std::array<WGPUFence,           MaxFrameInFlight>  m_GraphicFence;               /* @brief From WebGPUSwapChain, Array num equals to MaxFrameInFlight.     */

        // Use for Compute Queue.
        //WGPUCommandPool                                    m_ComputeCommandPool;         /* @brief From WebGPUCommandBuffer                                        */
        //std::array<WGPUCommandBuffer,   MaxFrameInFlight>  m_ComputeCommandBuffer;       /* @brief From WebGPUCommandBuffer, Array num equals to MaxFrameInFlight. */
        //std::array<WGPUSemaphore,       MaxFrameInFlight>  m_ComputeQueueSemaphore;      /* @brief From WebGPUSwapChain, Array num equals to MaxFrameInFlight.     */
        //std::array<WGPUFence,           MaxFrameInFlight>  m_ComputeFence;               /* @brief From WebGPUSwapChain, Array num equals to MaxFrameInFlight.     */
    };

    /**
    * @brief WebGPUObject Class.
    * This class defines the basic behaves of WebGPUObject.
    * When we create an new WebGPUObject, we need inherit from this.
    */
    class WebGPUObject : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        * Init member variables.
        * @param[in] webGPUState The global VulkanState.
        */
        WebGPUObject(WebGPUState& webGPUState)
                : m_WebGPUState(webGPUState)
        {}

        /**
        * @brief Destructor Function.
        * We destroy pipeline layout here.
        */
    	~WebGPUObject() override = default;

    protected:

        /**
        * @brief The global WebGPUState Referenced from WebGPURenderBackend.
        */
        WebGPUState& m_WebGPUState;
    };
}

#endif