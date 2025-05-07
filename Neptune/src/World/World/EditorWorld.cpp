/**
* @file EditorWorld.cpp.
* @brief The EditorWorld Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "EditorWorld.h"
#include "World/Entity.h"
#include "Render/FrameInfo.h"
#include "Systems/SystemManager.h"
#include "GamePlay/CameraController.h"

namespace Neptune {

	void EditorWorld::OnPreActivate()
	{
		NEPTUNE_PROFILE_ZONE;
		
		// camera
		{
			Entity cameraentity = CreateEntity("EditorCamera");
			CameraComponent& camComp = cameraentity.AddComponent<CameraComponent>(true);
			camComp.SetCamera(std::make_shared<Camera>());
			camComp.GetCamera()->SetPerspective(45.0f, 0.001f, 100000.0f);
			//camComp.GetCamera()->SetOrthographic(-100.0f, 100.0f, 100.0f, -100.0f, 0.001f, 100000.0f);
			TransformComponent& transformComp = cameraentity.GetComponent<TransformComponent>();
			transformComp.SetPosition({ 30.0f, 6.0f, 15.0f });
			transformComp.SetRotation({8.0f, -90.0f, 0.0f});

			cameraentity.AddComponent<NativeScriptComponent>(std::make_shared<CameraController>());
		}
	}
 
	void EditorWorld::OnActivate(TimeStep& ts)
	{
		NEPTUNE_PROFILE_ZONE;

		SystemManager::Run(ts);
	}

	void EditorWorld::OnDeactivate()
	{

	}
}