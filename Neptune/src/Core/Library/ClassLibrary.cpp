/**
* @file System.cpp.
* @brief The System Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ClassLibrary.h"
#include "StringLibrary.h"

namespace Neptune {

using namespace StringLibrary;

namespace ClassLibrary
{
    std::string GetClassString(ClassType t)
    {
        const std::vector<std::string>& outSplit = SplitString(t.get().name(), ':');
        return outSplit[outSplit.size() - 1];
    }
}
}