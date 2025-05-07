#include "GameEditorWorld.h"
#include <World/Entity.h>
#include <Resources/Loader/MaterialLoader.h>
#include <GamePlay/MeshController.h>
#include <Resources/ResourcePool/ResourcePool.h>
#include <Systems/ResourceSystem.h>
#include <Extensions/Gltf/GltfCollection.h>

namespace Neptune {

	void GameEditorWorld::OnPreActivate()
	{
		NEPTUNE_PROFILE_ZONE;

		ResourceSystem::RegistryResourceFolder(SPICES_GAME_ASSETS_PATH);

		EditorWorld::OnPreActivate();
	}

	void GameEditorWorld::OnActivate(TimeStep& ts)
	{
		NEPTUNE_PROFILE_ZONE;

		EditorWorld::OnActivate(ts);
	}

	void GameEditorWorld::OnDeactivate()
	{
		NEPTUNE_PROFILE_ZONE;

		EditorWorld::OnDeactivate();
	}

}