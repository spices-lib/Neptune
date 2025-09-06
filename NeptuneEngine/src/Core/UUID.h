/**
* @file UUID.h.
* @brief The UUID Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief This class helps to generate a uuid for one resource.
    */
    class UUID
    {
    public:

        /**
        * @brief Constructor Function.
        */
        UUID();

        /**
        * @brief Constructor Function.
        * 
        * @param[in] uuid Use given uuid as UUID.
        */
        UUID(uint64_t uuid);

        /**
        * @brief Destructor Function.
        */
        UUID(const UUID&) = default;

        /**
        * @brief Operator Function.
        * 
        * @return UUID.
        */
        operator uint64_t() const { return m_UUID; }

        /**
        * @brief Transform UUID to String.
        * 
        * @return Returns this UUID String.
        */
        std::string ToString() const;

    private:

        /**
        * @brief UUID.
        */
        uint64_t m_UUID;
    };

}

namespace std {

    template<>
    struct hash<Neptune::UUID>
    {
        std::size_t operator()(const Neptune::UUID& uuid) const noexcept
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}