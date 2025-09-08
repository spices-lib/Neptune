/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Class Implementation.
* @author Spices.
*/

#include "EditorWorld.h"
#include <EntryPoint.h>

namespace Neptune {

    SP<World> CreateWorld()
    {
        return CreateSP<EditorWorld>();
    }

}