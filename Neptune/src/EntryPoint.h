/**
* @file EntryPoint.h.
* @brief EntryPoint Definitions.
* @author Spices.
*/
#pragma once
#include "Core/Application.h"

/**
* @brief Main Function.
*/
inline int main() {

    const auto& engine = Neptune::Application::Instance();
    engine.Run();
    Neptune::Application::Destroy();

    return 0;
}
