/**
* @file WebGPUContext.cpp.
* @brief The WebGPUContext Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUContext.h"
#include "WebGPUInstance.h"
#include "WebGPUAdapter.h"
#include "WebGPUDevice.h"

namespace Neptune {

	void WebGPUContext::Registry(EWebGPUObject type, SP<WebGPUObject> object)
	{
		switch (type) 
		{
			case EWebGPUObject::WebGPUInstance:
			{
				if (auto p = std::dynamic_pointer_cast<WebGPUInstance>(object))
				{
					m_Instance = p;
				}
				else 
				{
					NEPTUNE_CORE_ERROR("WebGPU Instance registried failed.")
				}
				break;
			}
			case EWebGPUObject::WebGPUAdapter:
			{
				if (auto p = std::dynamic_pointer_cast<WebGPUAdapter>(object))
				{
					m_Adapter = p;
				}
				else
				{
					NEPTUNE_CORE_ERROR("WebGPU Adapter registried failed.")
				}
				break;
			}
			case EWebGPUObject::WebGPUDevice:
			{
				if (auto p = std::dynamic_pointer_cast<WebGPUDevice>(object))
				{
					m_Device = p;
				}
				else
				{
					NEPTUNE_CORE_ERROR("WebGPU Device registried failed.")
				}
				break;
			}
			default:
			{
				NEPTUNE_CORE_ERROR("Not known WebGPU Object registied.")
				break;
			}
		}
	}

}

#endif