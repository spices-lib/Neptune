/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Class Implementation.
* @author Spices.
*/

#include "World/RuntimeWorld.h"
#include "World/Scene/Scene.h"
#include <EntryPoint.h>

namespace Neptune {
    
    UP<World> CreateWorld()
    {
        return CreateUP<Runtime::RuntimeWorld>();
    }
    
}