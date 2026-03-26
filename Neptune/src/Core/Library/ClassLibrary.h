/**
* @file ClassLibrary.h.
* @brief The ClassLibrary Namespace Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::ClassLibrary {

/**
* @brief Using ClassType instead std::reference_wrapper<const std::type_info>.
*/
using ClassType = std::reference_wrapper<const std::type_info>;

    /**
    * @brief Get Class Name as string.
    * 
    * @param[in] t ClassType.
    * 
    * @return Returns Class Name.
    */
    std::string GetClassString(ClassType t);
}