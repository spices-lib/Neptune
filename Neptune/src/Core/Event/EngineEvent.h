/**
* @file EngineEvent.h.
* @brief The EngineEvent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"
#include "Core/Container/BitSet.hpp"

namespace Neptune {
    
    /**
    * @brief EngineEvent Bit
    */
    enum class EngineEventBit : uint32_t
    {
        StopTheEngine = 0,
        InitSlateFrontend,
        ShutdownSlateFrontend,

        Count
    };

    /**
    * @brief This Class is inherited from Event Class.
    * Inherit from it and create specific EngineEvent class.
    */
    class EngineEvent : public Event
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] flag Input EngineEventBit.
        */
        EngineEvent(const Container::BitSet<EngineEventBit>& flag)
            : m_Flag(flag)
        {}

        /**
        * @brief Constructor Function.
        * 
        * @param[in] bit Input EngineEventBit.
        */
        EngineEvent(EngineEventBit bit)
            : m_Flag(bit)
        {
            m_Flag.Set(bit, true);
        }

        /**
        * @brief Destructor Function.
        */
        ~EngineEvent() override = default;

        /**
        * @brief Is has bit.
        * 
        * @param[in] bit EngineEventBit.
        * 
        * @return Returns true if it has bit.
        */
        [[nodiscard]] bool Has(EngineEventBit bit) const { return m_Flag.Test(bit); }

        /**
        * @brief Serialize this Event Class to string.
        * 
        * @return Returns Serialized string.
        */
        std::string ToString() const override
        {
            NEPTUNE_PROFILE_ZONE

            using enum EngineEventBit;

            std::stringstream ss;
            ss << "EngineEvent: ";

            if (m_Flag.Test(StopTheEngine))         ss << "StopTheEngine ";
            if (m_Flag.Test(InitSlateFrontend))     ss << "InitSlateFrontend ";
            if (m_Flag.Test(ShutdownSlateFrontend)) ss << "ShutdownSlateFrontend ";

            return ss.str();
        }

        EVENT_CLASS_TYPE(Engine)
        EVENT_CLASS_CATEGORY(EventCategorySlate)

    private:

        Container::BitSet<EngineEventBit> m_Flag{};   // @brief EngineEventBit.
    };
}