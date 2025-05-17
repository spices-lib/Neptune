/**
* @file StringLibrary.h.
* @brief The StringLibrary Namespace Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

namespace StringLibrary
{
    /**
    * @brief Split a string to a string vector container use a char.
    * @param[in] input The string we want to split.
    * @param[in] delimiter The char we want to use.
    * @return Returns a string vector container.
    */
    std::vector<std::string> SplitString(const std::string& input, char delimiter);
}
}