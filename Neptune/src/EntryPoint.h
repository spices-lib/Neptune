/**
* @file EntryPoint.h.
* @brief EntryPoint Definitions.
* @author Spices.
*/
#pragma once
#include <emscripten.h>
#include <iostream>

EMSCRIPTEN_KEEPALIVE
int add(int a, int b)
{
    return a + b;
}

EMSCRIPTEN_KEEPALIVE
std::string wasmMain()
{
    return "Hello World\n";
}

/**
* @brief Main Function.
*/
int main() {

    return 0;
}