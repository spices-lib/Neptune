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

    /**
    * @brief Split a string to a string vector container use a char, keeps delimiter.
    * 
    * @param[in] input The string we want to split.
    * @param[in] delimiter The char we want to use.
    * 
    * @return Returns a string vector container.
    */
    std::vector<std::string> SplitKeepString(const std::string& input, char delimiter);

    /**
    * @brief If string equal.
    * 
    * @param[in] str0 First string.
    * @param[in] str1 Second string.
    * 
    * @return Returns true if equal.
    */
    bool StringsEqual(const char* str0, const char* str1);

    /**
    * @brief Convert char to wchar.
    * 
    * @param[in] c char.
    * 
    * @return Returns wchar.
    */
    std::wstring CharToWChar(const char* c);

    /**
    * @brief Convert wchar to char.
    * 
    * @param[in] wc wchar.
    * 
    * @return Returns char.
    */
    std::string WCharToChar(const wchar_t* wc);
}