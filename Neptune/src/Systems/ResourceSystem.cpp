/**
* @file ResourceSystem.cpp.
* @brief The ResourceSystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ResourceSystem.h"

namespace Neptune {

	std::vector<std::string> ResourceSystem::m_ResourceSearchFolder = { NEPTUNE_ASSETS_PATH };

	void ResourceSystem::OnSystemInitialize()
	{
		NEPTUNE_PROFILE_ZONE;

	}

	void ResourceSystem::OnSystemShutDown()
	{
		NEPTUNE_PROFILE_ZONE;


	}

	void ResourceSystem::OnSystemUpdate(TimeStep& ts)
	{
	}

	void ResourceSystem::OnEvent(Event& event)
	{
	}

	void ResourceSystem::RegistryResourceFolder(const std::string& folder)
	{
	}

}