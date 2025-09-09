/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Class Implementation.
* @author Spices.
*/

#include "World/EditorWorld.h"
#include "World/Scene/Scene.h"
#include <EntryPoint.h>

namespace Neptune {

    UP<World> CreateWorld()
    {
        return CreateUP<Editor::EditorWorld>();
    }

}