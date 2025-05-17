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

    auto engine = Neptune::Application::Create();
    engine->Run();

    return 0;
}