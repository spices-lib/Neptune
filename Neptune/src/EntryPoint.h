/**
* @file EntryPoint.h.
* @brief EntryPoint Definitions.
* @author Spices.
*/
#pragma once
#include <emscripten.h>
#include <iostream>
#include <GLFW/emscripten_glfw3.h>

EMSCRIPTEN_KEEPALIVE
int wasmMain()
{
    glfwInit();

    return 0;
}

/**
* @brief Main Function.
*/
int main() {
    return 0;
}