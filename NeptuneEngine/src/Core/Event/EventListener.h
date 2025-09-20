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
        EventListener() : m_Interested(EventType::None) {}

        /**
        * @brief Constructor Function.
        *
        * @param[in] type EventType.
        */
        explicit EventListener(EventType type) : m_Interested(type) {}

        /**
        * @brief Destructor Function.
        */
        virtual ~EventListener() = default;

        /**
         * @brief Registry interested event type.
         * 
         * @param type EventType.
         */
        void Registry(EventType type)
        {
            NEPTUNE_PROFILE_ZONE

            //m_Interested |= type;
        }

        /**
         * @brief UnRegistry interested event type.
         * 
         * @param type EventType.
         */
        void UnRegistry(EventType type)
        {
            NEPTUNE_PROFILE_ZONE

            //m_Interested &= ~type;
        }

        /**
         * @brief Dispatch interested event.
         * 
         * @param event Event
         */
        void Dispatch(Event& event)
        {
            NEPTUNE_PROFILE_ZONE

            /*if(event.GetEventType() & m_Interested == 0) {
                return;
            }*/

            OnEvent(event);
        }

        /**
         * @brief Interface of on Event triggered.
         * 
         * @param event Event
         */
        virtual void OnEvent(Event& event) = 0;

    private:

        /**
         * @brief Interested event type.
         */
        EventType m_Interested;
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