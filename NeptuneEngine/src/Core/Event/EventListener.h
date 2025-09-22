/**
* @file EventListener.h.
* @brief The EventListener Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

#include <memory.h>

namespace Neptune {

    class EventListener
    {
    public:
        
        /**
        * @brief Dispatch event to listener.
        * 
        * @param[in] event Event
        * @param[in] instance any pointer.
        */
        template<typename T>
        static void Dispatch(Event& event, T* instance);

    public:

        /**
        * @brief Constructor Function.
        */
        EventListener() = default;

        /**
        * @brief Constructor Function.
        *
        * @param[in] bit EventType.
        */
        explicit EventListener(EventType bit) 
        {
            Registry(bit);
        }

        /**
        * @brief Destructor Function.
        */
        virtual ~EventListener() = default;

        /**
        * @brief Registry interested event type.
        * 
        * @param[in] bit EventType.
        */
        void Registry(EventType bit)
        {
            NEPTUNE_PROFILE_ZONE

            m_Interested.Set(bit, true);
        }

        /**
        * @brief UnRegistry interested event type.
        * 
        * @param[in] bit EventType.
        */
        void UnRegistry(EventType bit)
        {
            NEPTUNE_PROFILE_ZONE

            m_Interested.Set(bit, false);
        }

        /**
        * @brief Dispatch interested event.
        * 
        * @param[in] event Event
        */
        void Dispatch(Event& event)
        {
            NEPTUNE_PROFILE_ZONE

            if(!m_Interested.Test(event.GetEventType())) 
            {
                return;
            }

            OnEvent(event);
        }

        /**
        * @brief Interface of on Event triggered.
        * 
        * @param[in] event Event
        */
        virtual void OnEvent(Event& event) = 0;

    private:

        /**
        * @brief Interested event type.
        */
        BitSet<EventType> m_Interested{};
    };

    template<typename T>
    void EventListener::Dispatch(Event& event, T* instance)
    {
        NEPTUNE_PROFILE_ZONE

        if(const auto p = dynamic_cast<EventListener*>(instance))
        {
            p->Dispatch(event);
        }
    }

}