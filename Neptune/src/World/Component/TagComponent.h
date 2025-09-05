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
    class TagComponent : public Component
    {
    public:

        /**
        * @brief Constructor Function.
        */
        TagComponent() = default;

        /**
        * @brief Constructor Function.
        */
        TagComponent(const std::string& tag) : m_Tags(tag) {}

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

        /**
        * @brief Get the tags variable.
        * 
        * @return Returns the tags variable.
        */
        const std::string& GetTag() { return m_Tags; }

    private:

        /**
        * @brief The tags this component handled.
        */
        std::string m_Tags;
    };
}