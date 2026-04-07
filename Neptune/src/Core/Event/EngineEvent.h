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

    enum class EngineEventBit : uint32_t
    {
        StopTheEngine           = 0,
        InitSlateFrontend       = 1,
        ShutdownSlateFrontend   = 2,

        Count                   = 3
    };

    class EngineEvent : public Event
    {
    public:

        EngineEvent(const Container::BitSet<EngineEventBit>& flag)
            : m_Flag(flag)
        {}

        EngineEvent(EngineEventBit bit)
            : m_Flag()
        {
            m_Flag.Set(bit, true);
        }

        ~EngineEvent() override = default;

        [[nodiscard]] bool Has(EngineEventBit bit) const { return m_Flag.Test(bit); }

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

        Container::BitSet<EngineEventBit> m_Flag;
    };
}