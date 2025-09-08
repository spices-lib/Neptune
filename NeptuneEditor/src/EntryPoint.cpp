/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Class Implementation.
* @author Spices.
*/

#include "World/EditorWorld.h"
#include <EntryPoint.h>

namespace Neptune::Editor {

    SP<World> CreateWorld()
    {
        return CreateSP<EditorWorld>();
    }

}