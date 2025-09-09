/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Class Implementation.
* @author Spices.
*/

#include "World/EditorWorld.h"
#include <EntryPoint.h>
#include <World/Scene/Scene.h>
namespace Neptune::Editor {

    UP<World> CreateWorld()
    {
        return CreateUP<EditorWorld>();
    }

}