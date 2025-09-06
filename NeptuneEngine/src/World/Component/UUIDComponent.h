/**
* @file UUIDComponent.h.
* @brief The UUIDComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Core/UUID.h"

namespace Neptune {

    /**
    * @brief UUIDComponent Class.
    * This class defines the specific behaves of UUIDComponent.
    */
    class UUIDComponent : public Component
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] uuid UUID.
        */
        UUIDComponent(UUID uuid) : m_uuid(uuid) {}

        /**
        * @brief Constructor Function.
        */
        UUIDComponent() : m_uuid(UUID()) {}

        /**
        * @brief Destructor Function.
        */
        ~UUIDComponent() override = default;

        /**
        * @brief Get the uuid variable.
        * 
        * @return Returns the uuid variable.
        */
        const UUID& GetUUID() const { return m_uuid; }

    private:

        /**
        * @brief The uuid this component handled.
        */
        UUID m_uuid;
    };
}