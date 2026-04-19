/**
* @file TagComponent.h.
* @brief The TagComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"

namespace Neptune {

    /**
    * @brief TagComponent Class.
    * This class defines the specific behaves of TagComponent.
    */
    class TagComponent : public Component<std::string>
    {
    public:

        /**
        * @brief Constructor Function.
        */
        TagComponent() = default;

        /**
        * @brief Constructor Function.
        */
        TagComponent(const std::string& tag) : Component(tag) {}

        /**
        * @brief Destructor Function.
        */
        ~TagComponent() override = default;

        /**
        * @brief Rename first element in tags.
        * 
        * @param[in] tag new name.
        */
        void Rename(const std::string& tag);

    };
}