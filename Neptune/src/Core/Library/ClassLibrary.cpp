/**
* @file ClassLibrary.cpp.
* @brief The ClassLibrary Namespace Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ClassLibrary.h"
#include "StringLibrary.h"

namespace Neptune::ClassLibrary {

using namespace StringLibrary;

    std::string GetClassString(ClassType t)
    {
        NEPTUNE_PROFILE_ZONE

        const auto& outSplit = SplitString(t.get().name(), ':');
        return outSplit[outSplit.size() - 1];
    }
}