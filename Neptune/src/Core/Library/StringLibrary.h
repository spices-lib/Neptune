/**
* @file StringLibrary.h.
* @brief The StringLibrary Namespace Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::StringLibrary {

    /**
    * @brief Split a string to a string vector container use a char.
    * 
    * @param[in] input The string we want to split.
    * @param[in] delimiter The char we want to use.
    * 
    * @return Returns a string vector container.
    */
    std::vector<std::string> SplitString(const std::string& input, char delimiter);

    static std::vector<std::string> SplitKeepString(const std::string& input, char delimiter);

    static bool StringsEqual(const char* str0, const char* str1);

    static std::wstring CharToWChar(const char* c);

    static std::string WCharToChar(const wchar_t* wc);
}