#include <EntryPoint.h>
#include "GameEditorWorld.h"
#include <Core/Memory/MemoryPool.h>

namespace Neptune {

	std::shared_ptr<World> CreateWorld()
	{
		NEPTUNE_PROFILE_ZONE;

		return std::make_shared<GameEditorWorld>();
	}
}