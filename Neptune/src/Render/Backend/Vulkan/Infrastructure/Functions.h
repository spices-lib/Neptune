/**
* @file Functions.h.
* @brief The Functions Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {

#define VK_FUNCTION_POINTER(function)          \
	PFN_##function function = nullptr;

#define EXPLAIN_VK_FUNCTION_POINTER(function)  \
	function = reinterpret_cast<PFN_##function>(vkGetInstanceProcAddr(instance, #function));  \
	if(!function){                                                                            \
		std::stringstream ss;                                                                 \
		ss << "Vulkan Function: " << #function << " Not found.";                              \
		NEPTUNE_CORE_ERROR(ss.str())                                                          \
	}

	using IFunctions = IInfrastructure<class Functions, EInfrastructure::Functions>;

	/**
	* @brief Vulkan::Functions Class.
	* This class defines the Vulkan::Functions behaves.
	*/
	class Functions : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Functions(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Functions() override = default;

		/**
		* @brief Initialize.
		* 
		* @param[in] instance VkInstance
		*/
		void Init(VkInstance instance);

		/** 
		* @brief Debug Functions.
		*/
		VK_FUNCTION_POINTER(vkCreateDebugUtilsMessengerEXT                  )
		VK_FUNCTION_POINTER(vkDestroyDebugUtilsMessengerEXT                 )
		VK_FUNCTION_POINTER(vkGetDeviceFaultInfoEXT                         )

		/**
		* @brief DebugUtils Function. 
		*/
		VK_FUNCTION_POINTER(vkCmdBeginDebugUtilsLabelEXT                    )
		VK_FUNCTION_POINTER(vkCmdEndDebugUtilsLabelEXT                      )
		VK_FUNCTION_POINTER(vkCmdInsertDebugUtilsLabelEXT                   )
														                    
		VK_FUNCTION_POINTER(vkQueueBeginDebugUtilsLabelEXT                  )
		VK_FUNCTION_POINTER(vkQueueEndDebugUtilsLabelEXT                    )
		VK_FUNCTION_POINTER(vkQueueInsertDebugUtilsLabelEXT                 )
														                    
		VK_FUNCTION_POINTER(vkSetDebugUtilsObjectNameEXT                    )
		VK_FUNCTION_POINTER(vkSetDebugUtilsObjectTagEXT                     )
																            
		/**														            
		* @brief RayTracing Function.					            
		*/														            
		VK_FUNCTION_POINTER(vkGetRayTracingShaderGroupHandlesKHR            )
		VK_FUNCTION_POINTER(vkCmdTraceRaysKHR                               )
		VK_FUNCTION_POINTER(vkCreateRayTracingPipelinesKHR                  )
		VK_FUNCTION_POINTER(vkCreateAccelerationStructureKHR                )
		VK_FUNCTION_POINTER(vkDestroyAccelerationStructureKHR               )
		VK_FUNCTION_POINTER(vkCmdBuildAccelerationStructuresKHR             )
		VK_FUNCTION_POINTER(vkCopyAccelerationStructureKHR                  )
		VK_FUNCTION_POINTER(vkGetAccelerationStructureDeviceAddressKHR      )
		VK_FUNCTION_POINTER(vkCmdWriteAccelerationStructuresPropertiesKHR   )
		VK_FUNCTION_POINTER(vkGetAccelerationStructureBuildSizesKHR         )
		VK_FUNCTION_POINTER(vkCmdCopyAccelerationStructureKHR               )

		/**
		* @brief Mesh Shader Function.
		*/
		VK_FUNCTION_POINTER(vkCmdDrawMeshTasksEXT                           )

		/**
		* @brief DGC Function.
		*/
		VK_FUNCTION_POINTER(vkCreateIndirectCommandsLayoutNV                )
		VK_FUNCTION_POINTER(vkDestroyIndirectCommandsLayoutNV               )
		VK_FUNCTION_POINTER(vkCmdExecuteGeneratedCommandsNV                 )
		VK_FUNCTION_POINTER(vkGetGeneratedCommandsMemoryRequirementsNV      )
		VK_FUNCTION_POINTER(vkCmdPreprocessGeneratedCommandsNV              )

		/**
		* @brief Aftermath Function.
		*/
		VK_FUNCTION_POINTER(vkCmdSetCheckpointNV                            )

		/**
		* @brief Tracy Vulkan Context Collect Function
		*/
		VK_FUNCTION_POINTER(vkGetPhysicalDeviceCalibrateableTimeDomainsEXT  )
		VK_FUNCTION_POINTER(vkGetCalibratedTimestampsEXT                    )
		VK_FUNCTION_POINTER(vkResetQueryPool                                )

		/**
		* @brief Copy data to image from host directly.
		*/
		VK_FUNCTION_POINTER(vkCopyMemoryToImageEXT                          )
		VK_FUNCTION_POINTER(vkCopyImageToMemoryEXT                          )

		/**
		* @brief Video Encode/Decode
		*/
		VK_FUNCTION_POINTER(vkGetPhysicalDeviceVideoCapabilitiesKHR         )
		VK_FUNCTION_POINTER(vkCreateVideoSessionParametersKHR               )
		VK_FUNCTION_POINTER(vkDestroyVideoSessionParametersKHR              )
		VK_FUNCTION_POINTER(vkUpdateVideoSessionParametersKHR               )
		VK_FUNCTION_POINTER(vkGetPhysicalDeviceVideoFormatPropertiesKHR     )
		VK_FUNCTION_POINTER(vkGetVideoSessionMemoryRequirementsKHR          )
		VK_FUNCTION_POINTER(vkBindVideoSessionMemoryKHR                     )
		VK_FUNCTION_POINTER(vkCreateVideoSessionKHR                         )
		VK_FUNCTION_POINTER(vkDestroyVideoSessionKHR                        )
		VK_FUNCTION_POINTER(vkCmdBeginVideoCodingKHR                        )
		VK_FUNCTION_POINTER(vkCmdControlVideoCodingKHR                      )
		VK_FUNCTION_POINTER(vkCmdDecodeVideoKHR                             )
		VK_FUNCTION_POINTER(vkCmdEndVideoCodingKHR                          )

		/**
		* @brief Optical Flow.
		*/
		VK_FUNCTION_POINTER(vkCreateOpticalFlowSessionNV                   )
		VK_FUNCTION_POINTER(vkDestroyOpticalFlowSessionNV                  )
		VK_FUNCTION_POINTER(vkCmdOpticalFlowExecuteNV                      )
		VK_FUNCTION_POINTER(vkGetPhysicalDeviceOpticalFlowImageFormatsNV   )
		VK_FUNCTION_POINTER(vkBindOpticalFlowSessionImageNV                )
	};
	
}

#endif