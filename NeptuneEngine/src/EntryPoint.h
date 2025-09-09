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

    auto& engine = Neptune::Application::Instance();
    engine.Run();
    Neptune::Application::Destroy();

    return 0;
}
