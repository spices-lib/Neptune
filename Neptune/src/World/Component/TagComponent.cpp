/**
* @file TagComponent.cpp.
* @brief The TagComponent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "TagComponent.h"

namespace Neptune {

    void TagComponent::Rename(const std::string& tag)
    {
        NEPTUNE_PROFILE_ZONE

        m_Tags = tag;
    }
}
