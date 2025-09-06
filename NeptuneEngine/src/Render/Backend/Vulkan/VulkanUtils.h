/**
* @file VulkanUtils.h.
* @brief The VulkanObject Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanFunctions.h"
#include "vk_mem_alloc.h"

#include <vulkan/vulkan.h>

namespace Neptune {

/**
* @brief Max In Flight Frame.
* 2 buffers are enough in windows.
*/
constexpr uint32_t MaxFrameInFlight = 2;

/**
* @brief Use VMA for memory allocate.
*/
#define VMA_ALLOCATOR 1

/**
* @brief Disable Host Image copy for host memory heap is too smaller.
*/
#define VKImageHostOperation 0

	/**
	* @brief Handle VkResult Function.
	* @param[in] result VkResult.
	*/
	static void HandleVkResult(VkResult result)
	{
		if (result == VK_SUCCESS) return;

		switch (result)
		{
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			{
				NEPTUNE_CORE_CRITICAL("Video Memory has already run out.")
				break;
			}
			case VK_ERROR_DEVICE_LOST:
			{
				NEPTUNE_CORE_CRITICAL("Device has losted, Start Aftermath...")
				break;
			}
			default:
			{
				NEPTUNE_CORE_ERROR("Render backend throw error.")
				break;
			}
		}
	}

	/**
	* @brief Vulkan Check macro.
	* Verify Vulkan API Effectiveness.
	*/
	#define VK_CHECK(expr)  { auto expr_value = expr;  ASSERT(expr_value == VK_SUCCESS);  HandleVkResult(expr_value); }

	/**
	* @brief This struct contains all Vulkan object in used global.
	*/
	struct VulkanState : NonCopyable
	{
		/**
		* @brief Constructor Function.
		*/
		VulkanState() = default;
		
		VkInstance                                       m_Instance;                   /* @brief From VulkanInstance.                                            */
		VkSurfaceKHR                                     m_Surface;                    /* @brief From VulkanInstance.                                            */
		VkPhysicalDevice                                 m_PhysicalDevice;             /* @brief From VulkanDevice.                                              */
		VkDevice                                         m_Device;                     /* @brief From VulkanDevice.                                              */
		VmaAllocator                                     m_VmaAllocator;               /* @brief From VulkanMemoryAllocator.                                     */
		VulkanFunctions                                  m_VkFunc;                     /* @brief From VulkanFunctions.                                           */
		VkQueue											 m_GraphicQueue;               /* @brief From VulkanDevice, Queue for graphic compute.                   */
		uint32_t                                         m_GraphicQueueFamily;         /* @brief From VulkanDevice, ID for graphic queue.                        */
		VkQueue											 m_PresentQueue;               /* @brief From VulkanDevice, Queue for present windows.                   */
		VkQueue											 m_TransferQueue;              /* @brief From VulkanDevice, Queue for transfer buffer.                   */
		VkQueue											 m_ComputeQueue;               /* @brief From VulkanDevice, Queue for compute shader.                    */
		uint32_t                                         m_ComputeQueueFamily;         /* @brief From VulkanDevice, ID for compute queue.                        */
		VkSwapchainKHR                                   m_SwapChain;                  /* @brief From VulkanSwapChain.                                           */
		std::array<VkImage,           MaxFrameInFlight>  m_SwapChainImages;            /* @brief The SwapChain's image, used for present.                        */
		std::array<VkImageView,       MaxFrameInFlight>  m_SwapChainImageViews;        /* @brief The SwapChain's imageView.                                      */
		std::array<VkSampler,         MaxFrameInFlight>  m_SwapChainImageSamplers;     /* @brief The SwapChain's imageSampler.                                   */
	  													 
		// Used for Graphic Queue	  					 
		VkCommandPool                                    m_GraphicCommandPool;         /* @brief From VulkanCommandBuffer                                        */
		std::array<VkCommandBuffer,   MaxFrameInFlight>  m_GraphicCommandBuffer;       /* @brief From VulkanCommandBuffer, Array num equals to MaxFrameInFlight. */
		std::array<VkSemaphore,       MaxFrameInFlight>  m_GraphicImageSemaphore;      /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
		std::array<VkSemaphore,       MaxFrameInFlight>  m_GraphicQueueSemaphore;      /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
		std::array<VkFence,           MaxFrameInFlight>  m_GraphicFence;               /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
									  					 
		// Use for Compute Queue.	  					 
		VkCommandPool                                    m_ComputeCommandPool;         /* @brief From VulkanCommandBuffer                                        */
		std::array<VkCommandBuffer,   MaxFrameInFlight>  m_ComputeCommandBuffer;       /* @brief From VulkanCommandBuffer, Array num equals to MaxFrameInFlight. */
		std::array<VkSemaphore,       MaxFrameInFlight>  m_ComputeQueueSemaphore;      /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
		std::array<VkFence,           MaxFrameInFlight>  m_ComputeFence;               /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
	};
	
	/**
	* @brief VulkanObject Class.
	* This class defines the basic behaves of VulkanObject.
	* When we create an new VulkanObject, we need inherit from this.
	*/
	class VulkanObject : public NonCopyable
	{
	public:

		/**
		* @brief Constructor Function.
		* Init member variables.
		* @param[in] vulkanState The global VulkanState.
		*/
		VulkanObject(VulkanState& vulkanState) 
			: m_VulkanState(vulkanState)
		{}

		/**
		* @brief Destructor Function.
		* We destroy pipeline layout here.
		*/
		~VulkanObject() override = default;

	protected:

		/**
		* @brief The global VulkanState Referenced from VulkanRenderBackend.
		*/
		VulkanState& m_VulkanState;
	};

}

#endif