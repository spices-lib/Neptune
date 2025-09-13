/**
* @file VulkanInfrastructure.cpp.
* @brief The VulkanInfrastructure Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanInfrastructure.h"

namespace Neptune {

	VulkanInfrastructure::VulkanInfrastructure(VulkanContext& context)
		: m_Context(context)
	{}

	VulkanInfrastructure::~VulkanInfrastructure()
	{
		Destroy(this);
	}

}

#endif