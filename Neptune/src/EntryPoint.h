/**
* @file EntryPoint.h.
* @brief EntryPoint Definitions.
* @author Spices.
*/
#pragma once

#include "Core/Core.h"
#include "Core/Application.h"

/**
* @brief Main Function.
*/
int main() {

    NEPTUNE_CORE_TRACE("Neptune Entry");
    auto engine = Neptune::Application::Create();
    if(engine)
    {
        NEPTUNE_CORE_TRACE("Neptune Application Created succeed.");
    }
    else
    {
        NEPTUNE_CORE_CRITICAL("Neptune Application Created failed.");
        return -1;
    }

    engine->Run();

    return 0;
}